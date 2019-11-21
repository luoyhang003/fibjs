/*
 * HEKey.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: luoyhang003
 */

#include "object.h"
#include "ifs/he.h"
#include "Buffer.h"
#include "Ciphertext.h"
#include "encoding.h"
#include "HEKey.h"

namespace fibjs {

result_t HEKey_base::_new(obj_ptr<HEKey_base>& retVal, v8::Local<v8::Object> This)
{
    return CHECK_ERROR(Runtime::setError("HEKey: default constructor unsupported."));
}

result_t HEKey_base::_new(int32_t scheme_type, int32_t poly_modulus_degree, int32_t plain_modulus, obj_ptr<HEKey_base>& retVal, 
    v8::Local<v8::Object> This)
{
    if(scheme_type != 1)
        return CHECK_ERROR(Runtime::setError("HEKey: unsupported scheme."));

    retVal = new HEKey(poly_modulus_degree, plain_modulus);
    return 0;
}

result_t HEKey_base::_new(int32_t scheme_type, int32_t poly_modulus_degree, int32_t scale, v8::Local<v8::Array> coeff_modulus,
    obj_ptr<HEKey_base>& retVal, v8::Local<v8::Object> This)
{
    if(scheme_type != 2)
        return CHECK_ERROR(Runtime::setError("HEKey: unsupported scheme."));
    
    int32_t len = coeff_modulus->Length();
    std::vector<int32_t> vec;
    vec.reserve(len);
    result_t hr;

    for (int32_t i = 0; i < len; i++) {
        int32_t num;
        hr = GetArgumentValue(JSValue(coeff_modulus->Get(i)), num);
        if (hr < 0)
            return CHECK_ERROR(hr);
        vec.push_back(num);
    }
    retVal = new HEKey(poly_modulus_degree, scale, vec);
    return 0;
}

HEKey::HEKey()
{
    HEKey(4096, 1024);
}

HEKey::HEKey(const int32_t& poly_modulus_degree, const int32_t& plain_modulus)
{
    m_scheme_type = 1;

    m_poly_modulus_degree = poly_modulus_degree;
    m_plain_modulus = plain_modulus;

    seal::EncryptionParameters parms(m_scheme_type);
    parms.set_poly_modulus_degree((size_t)m_poly_modulus_degree);

    parms.set_coeff_modulus(seal::CoeffModulus::BFVDefault(m_poly_modulus_degree));
    parms.set_plain_modulus(m_plain_modulus);

    m_seal_context = seal::SEALContext::Create(parms);
    m_key = new seal::KeyGenerator(m_seal_context);
}

HEKey::HEKey(const int32_t& poly_modulus_degree, const int32_t& scale, const std::vector<int32_t>& coeff_modulus)
{
    m_scheme_type = 2;
    m_poly_modulus_degree = poly_modulus_degree;
    m_coeff_modulus = coeff_modulus;
    m_scale = scale;

    seal::EncryptionParameters parms(m_scheme_type);
    parms.set_poly_modulus_degree((size_t)m_poly_modulus_degree);
    parms.set_coeff_modulus(seal::CoeffModulus::Create(m_poly_modulus_degree, m_coeff_modulus));

    m_seal_context = seal::SEALContext::Create(parms);
    m_key = new seal::KeyGenerator(m_seal_context);
}

HEKey::~HEKey()
{
}

result_t HEKey::get_scheme_type(exlib::string& retVal)
{
    switch (m_scheme_type)
    {
    case 1:
        retVal = "BFV";
        break;

    case 2:
        retVal = "CKKS";
        break;
    }
    return 0;
}
result_t HEKey::get_poly_modulus_degree(int32_t& retVal)
{
    retVal = m_poly_modulus_degree;
    return 0;
}
result_t HEKey::get_plain_modulus(int32_t& retVal)
{
    retVal = m_plain_modulus;
    return 0;
}

result_t HEKey::get_scale(int32_t& retVal)
{
    retVal = m_scale;
    return 0;
}

result_t HEKey::get_coeff_modulus(v8::Local<v8::Array>& retVal)
{
    v8::Isolate* isolate = holder()->m_isolate;
    v8::Local<v8::Array> arr = v8::Array::New(isolate);
    
    for(int i = 0; i < m_coeff_modulus.size(); i++)
        arr->Set(i, v8::Number::New(isolate, m_coeff_modulus[i]));
    retVal = arr;
    return 0;
}

result_t HEKey::genKey()
{
    m_public_key = m_key->public_key();
    m_secret_key = m_key->secret_key();
    m_relin_keys = m_key->relin_keys();

    return 0;
}

result_t HEKey::importKey(Buffer_base* priKey)
{
    int32_t sz;
    priKey->get_length(sz);

    seal::SEAL_BYTE *secret_key_bytes = new seal::SEAL_BYTE[sz];
    
    exlib::string str;
    priKey->toString(str);
    memcpy(secret_key_bytes, str.c_str(), sz);

    m_secret_key.load(m_seal_context, secret_key_bytes, sz);
 
    seal::KeyGenerator new_keygen(m_seal_context, m_secret_key);
    m_public_key = new_keygen.public_key();
    m_relin_keys = new_keygen.relin_keys();

    return 0;
}

result_t HEKey::exportKey(obj_ptr<Buffer_base>& retVal)
{
    long long int secret_key_size = m_secret_key.save_size(seal::Serialization::compr_mode_default);

    seal::SEAL_BYTE *secret_key_bytes = new seal::SEAL_BYTE[secret_key_size];
    
    m_secret_key.save(secret_key_bytes, secret_key_size);

    retVal = new Buffer(secret_key_bytes, secret_key_size);
    return 0;
}

result_t HEKey::encrypt(double number, obj_ptr<Ciphertext_base>& retVal)
{

    if(m_scheme_type == 1) {
        seal::IntegerEncoder encoder(m_seal_context);
        seal::Plaintext plain_number = encoder.encode((uint64_t)std::round(number));
        seal::Ciphertext encrypted;

        seal::Encryptor encryptor(m_seal_context, m_public_key);
        encryptor.encrypt(plain_number, encrypted);

        obj_ptr<Ciphertext_base> cipher = new Ciphertext(this, encrypted);

        retVal = cipher;
    } else {
        seal::CKKSEncoder encoder(m_seal_context);
        seal::Plaintext plain_number;
        seal::Ciphertext encrypted;

        encoder.encode(number, std::pow(2.0, m_scale), plain_number);

        seal::Encryptor encryptor(m_seal_context, m_public_key);
        encryptor.encrypt(plain_number, encrypted);

        obj_ptr<Ciphertext_base> cipher = new Ciphertext(this, encrypted);
        retVal = cipher;
    }
    return 0;
}

result_t HEKey::decrypt(Ciphertext_base* ciphertext, double& retVal)
{
    if(m_scheme_type == 1) {
        seal::Plaintext decrypted;
        seal::Decryptor decryptor(m_seal_context, m_secret_key);
        decryptor.decrypt(((Ciphertext*)ciphertext)->m_data, decrypted);
        
        seal::IntegerEncoder encoder(m_seal_context);

        retVal = std::round(encoder.decode_int32(decrypted));
    } else {
        seal::Plaintext decrypted;
        seal::CKKSEncoder encoder(m_seal_context);
        seal::Decryptor decryptor(m_seal_context, m_secret_key);
        decryptor.decrypt(((Ciphertext*)ciphertext)->m_data, decrypted);
        
        std::vector<double> result;
        encoder.decode(decrypted, result);

        retVal = result[0];
    }
    return 0;
}

result_t HEKey::toString(exlib::string& retVal)
{
    long long int secret_key_size = m_secret_key.save_size(seal::Serialization::compr_mode_default);

    seal::SEAL_BYTE *secret_key_bytes = new seal::SEAL_BYTE[secret_key_size];    
    m_secret_key.save(secret_key_bytes, secret_key_size);

    exlib::string strData;
    Buffer* buf = new Buffer(secret_key_bytes, secret_key_size); 
    buf->toString(strData);

    return base64Encode(strData, true, retVal);
}

result_t HEKey::toJSON(exlib::string key, v8::Local<v8::Value>& retVal)
{    
    Isolate* isolate = holder();
    v8::Local<v8::Object> o = v8::Object::New(isolate->m_isolate);

    exlib::string type = "";

    switch (m_scheme_type)
    {
    case 1:
        type = "BFV";
        break;
    
    case 2:
        type = "CKKS";
        break;
    }

    o->Set(isolate->NewString("scheme_type"), isolate->NewString(type));

    retVal = o;
    return 0;
}
}