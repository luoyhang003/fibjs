/*
 * Ciphertext.h
 *
 *  Created on: Nov 7, 2019
 *      Author: luoyhang003
 */

#include "ifs/Ciphertext.h"
#include "HEKey.h"
#include <seal/seal/seal.h>

#ifndef CIPHERTEXT_H_
#define CIPHERTEXT_H_

namespace fibjs {

class Ciphertext : public Ciphertext_base {
public:
    Ciphertext();
    Ciphertext(seal::Ciphertext cipher);
    Ciphertext(HEKey* key, seal::Ciphertext cipher);
    ~Ciphertext();

public:
    // object_base
    virtual result_t toString(exlib::string& retVal);
    virtual result_t toJSON(exlib::string key, v8::Local<v8::Value>& retVal);

public:
    // Ciphertext_base
    virtual result_t get_encrypted_data(obj_ptr<Buffer_base>& retVal);
    virtual result_t loadData(Buffer_base* buf);
    virtual result_t loadKey(HEKey_base* key);
    virtual result_t add(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t add(double number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t sub(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t sub(double number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t multiply(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t multiply(double number, obj_ptr<Ciphertext_base>& retVal);
    virtual result_t negate(obj_ptr<Ciphertext_base>& retVal);
    virtual result_t square(obj_ptr<Ciphertext_base>& retVal);
    virtual result_t relinearize(obj_ptr<Ciphertext_base>& retVal);

public:
    HEKey *m_key;
    seal::Ciphertext m_data;
};


} /* namespace fibjs */
#endif /* CIPHERTEXT_H_ */
