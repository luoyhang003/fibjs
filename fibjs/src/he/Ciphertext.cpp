/*
 * HEKey.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: luoyhang003
 */

#include "object.h"
#include "ifs/Ciphertext.h"
#include "Buffer.h"
#include "Ciphertext.h"
#include "HEKey.h"
#include <seal/seal/seal.h>

namespace fibjs {

result_t Ciphertext_base::_new(obj_ptr<Ciphertext_base>& retVal, v8::Local<v8::Object> This)
{
    retVal = new Ciphertext();
    return 0;
}

Ciphertext::Ciphertext()
{
}

Ciphertext::Ciphertext(seal::Ciphertext cipher)
{
    m_data = cipher;
}

Ciphertext::Ciphertext(HEKey* key, seal::Ciphertext cipher)
{
    m_key = key;
    m_data = cipher;
}

Ciphertext::~Ciphertext()
{
}

result_t Ciphertext::get_encrypted_data(obj_ptr<Buffer_base>& retVal)
{
    long long int size = m_data.save_size(seal::Serialization::compr_mode_default);
    seal::SEAL_BYTE *bytes = new seal::SEAL_BYTE[size];
    m_data.save(bytes, size);

    retVal = new Buffer(bytes, size);
    return 0;
}

result_t Ciphertext::loadData(Buffer_base* buf)
{
    int32_t sz;
    buf->get_length(sz);

    seal::SEAL_BYTE *bytes = new seal::SEAL_BYTE[sz];
    
    exlib::string str;
    buf->toString(str);
    memcpy(bytes, str.c_str(), sz);
    m_data.load(m_key->m_seal_context, bytes, sz);

    return 0;
}

result_t Ciphertext::loadKey(HEKey_base* key)
{
    m_key = (HEKey*)key;

    return 0;
}

result_t Ciphertext::add(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal)
{
    if(((Ciphertext*)cipher_number)->m_key->m_scheme_type != m_key->m_scheme_type)
        return CHECK_ERROR(Runtime::setError("Ciphertext: mixed scheme calculation."));

    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try {
        evaluator.add(((Ciphertext*)cipher_number)->m_data, m_data, result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::add(double number, obj_ptr<Ciphertext_base>& retVal)
{
    seal::Ciphertext result;
    seal::Evaluator evaluator(m_key->m_seal_context);

    try {
        if(m_key->m_scheme_type == 1) {
            seal::IntegerEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number = encoder.encode((uint64_t)std::round(number));
            evaluator.add_plain(m_data, plain_number, result);
        } else {
            seal::CKKSEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number;
            encoder.encode(number, std::pow(2.0, m_key->m_scale), plain_number);
            evaluator.add_plain(m_data, plain_number, result);
        }
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::sub(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal)
{
    if(((Ciphertext*)cipher_number)->m_key->m_scheme_type != m_key->m_scheme_type)
        return CHECK_ERROR(Runtime::setError("Ciphertext: mixed scheme calculation."));
    
    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try {
        evaluator.sub(m_data, ((Ciphertext*)cipher_number)->m_data, result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::sub(double number, obj_ptr<Ciphertext_base>& retVal)
{
    seal::Ciphertext result;
    seal::Evaluator evaluator(m_key->m_seal_context);

    try{
        if(m_key->m_scheme_type == 1) {
            seal::IntegerEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number = encoder.encode((uint64_t)std::round(number));
            evaluator.sub_plain(m_data, plain_number, result);
        } else {
            seal::CKKSEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number;
            encoder.encode(number, std::pow(2.0, m_key->m_scale), plain_number);
            evaluator.sub_plain(m_data, plain_number, result);
        }
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::multiply(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal)
{
    if(((Ciphertext*)cipher_number)->m_key->m_scheme_type != m_key->m_scheme_type)
        return CHECK_ERROR(Runtime::setError("Ciphertext: mixed scheme calculation."));
    
    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try {
        evaluator.multiply(((Ciphertext*)cipher_number)->m_data, m_data, result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::multiply(double number, obj_ptr<Ciphertext_base>& retVal)
{
    seal::Ciphertext result;
    seal::Evaluator evaluator(m_key->m_seal_context);

    try{
        if(m_key->m_scheme_type == 1) {
            seal::IntegerEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number = encoder.encode((uint64_t)std::round(number));
            evaluator.multiply_plain(m_data, plain_number, result);
        } else {
            seal::CKKSEncoder encoder(m_key->m_seal_context);
            seal::Plaintext plain_number;
            encoder.encode(number, std::pow(2.0, m_key->m_scale), plain_number);
            evaluator.multiply_plain(m_data, plain_number, result);
        }
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::negate(obj_ptr<Ciphertext_base>& retVal)
{
    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try{
        evaluator.negate(m_data, result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::square(obj_ptr<Ciphertext_base>& retVal)
{
    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try {
        evaluator.square(m_data, result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::relinearize(obj_ptr<Ciphertext_base>& retVal)
{
    seal::Evaluator evaluator(m_key->m_seal_context);
    seal::Ciphertext result;

    try {
        evaluator.relinearize(m_data, m_key->m_relin_keys, result);
        if(m_key->m_scheme_type == 2)
            evaluator.rescale_to_next_inplace(result);
    } catch(std::exception& e) {
        return CHECK_ERROR(Runtime::setError(e.what()));
    }

    retVal = new Ciphertext(m_key, result);
    return 0;
}

result_t Ciphertext::toString(exlib::string& retVal)
{
    retVal = "";
    return 0;
}

result_t Ciphertext::toJSON(exlib::string key, v8::Local<v8::Value>& retVal)
{
    Isolate* isolate = holder();

    v8::Local<v8::Object> o = v8::Object::New(isolate->m_isolate);

    retVal = o;
    return 0;
}
}
