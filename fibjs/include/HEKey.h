/*
 * HEKey.h
 *
 *  Created on: Aug 2, 2012
 *      Author: lion
 */

#include "ifs/HEKey.h"
#include <seal/seal/seal.h>

#ifndef HEKEY_H_
#define HEKEY_H_

namespace fibjs {

class HEKey : public HEKey_base {
public:
    HEKey();
    HEKey(const int32_t& poly_modulus_degree, const int32_t& plain_modulus);
    HEKey(const int32_t& poly_modulus_degree, const int32_t& scale, const std::vector<int32_t>& coeff_modulus);
    ~HEKey();

public:
    // object_base
    virtual result_t toString(exlib::string& retVal);
    virtual result_t toJSON(exlib::string key, v8::Local<v8::Value>& retVal);

public:
    // HEKey_base
    virtual result_t get_scheme_type(exlib::string& retVal);
    virtual result_t get_poly_modulus_degree(int32_t& retVal);
    virtual result_t get_plain_modulus(int32_t& retVal);
    virtual result_t get_scale(int32_t& retVal);
    virtual result_t get_coeff_modulus(v8::Local<v8::Array>& retVal);
    virtual result_t genKey();
    virtual result_t importKey(Buffer_base* priKey);
    virtual result_t exportKey(obj_ptr<Buffer_base>& retVal);
    virtual result_t encrypt(double number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t decrypt(Ciphertext_base* ciphertext, double& retVal);

public:
    uint16_t m_scheme_type = 1;
    size_t m_poly_modulus_degree = 4096;
    int32_t m_plain_modulus = 1024;
    int32_t m_scale = 60;
    std::vector<int32_t> m_coeff_modulus = {60, 40, 40, 60};

    std::shared_ptr<seal::SEALContext> m_seal_context;

    seal::KeyGenerator *m_key;
    seal::Encryptor *m_encryptor;
    seal::Decryptor *m_decryptor;

    seal::PublicKey m_public_key;
    seal::SecretKey m_secret_key;
    seal::RelinKeys m_relin_keys;
};

} /* namespace fibjs */
#endif /* HEKEY_H_ */
