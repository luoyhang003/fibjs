/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _Ciphertext_base_H_
#define _Ciphertext_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs {

class Buffer_base;
class HEKey_base;

class Ciphertext_base : public object_base {
    DECLARE_CLASS(Ciphertext_base);

public:
    // Ciphertext_base
    static result_t _new(obj_ptr<Ciphertext_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t get_encrypted_data(obj_ptr<Buffer_base>& retVal) = 0;
    virtual result_t loadData(Buffer_base* buf) = 0;
    virtual result_t loadKey(HEKey_base* key) = 0;
    virtual result_t add(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t add(double number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t sub(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t sub(double number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t multiply(Ciphertext_base* cipher_number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t multiply(double number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t negate(obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t square(obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t relinearize(obj_ptr<Ciphertext_base>& retVal) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_encrypted_data(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_loadData(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_loadKey(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_add(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_sub(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_multiply(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_negate(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_square(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_relinearize(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

#include "ifs/Buffer.h"
#include "ifs/HEKey.h"

namespace fibjs {
inline ClassInfo& Ciphertext_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "loadData", s_loadData, false },
        { "loadKey", s_loadKey, false },
        { "add", s_add, false },
        { "sub", s_sub, false },
        { "multiply", s_multiply, false },
        { "negate", s_negate, false },
        { "square", s_square, false },
        { "relinearize", s_relinearize, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "encrypted_data", s_get_encrypted_data, block_set, false }
    };

    static ClassData s_cd = {
        "Ciphertext", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void Ciphertext_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void Ciphertext_base::__new(const T& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("new Ciphertext()");
    CONSTRUCT_ENTER();

    METHOD_OVER(0, 0);

    hr = _new(vr, args.This());

    CONSTRUCT_RETURN();
}

inline void Ciphertext_base::s_get_encrypted_data(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<Buffer_base> vr;

    METHOD_NAME("Ciphertext.encrypted_data");
    METHOD_INSTANCE(Ciphertext_base);
    PROPERTY_ENTER();

    hr = pInst->get_encrypted_data(vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_loadData(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("Ciphertext.loadData");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Buffer_base>, 0);

    hr = pInst->loadData(v0);

    METHOD_VOID();
}

inline void Ciphertext_base::s_loadKey(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("Ciphertext.loadKey");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<HEKey_base>, 0);

    hr = pInst->loadKey(v0);

    METHOD_VOID();
}

inline void Ciphertext_base::s_add(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.add");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Ciphertext_base>, 0);

    hr = pInst->add(v0, vr);

    METHOD_OVER(1, 1);

    ARG(double, 0);

    hr = pInst->add(v0, vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_sub(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.sub");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Ciphertext_base>, 0);

    hr = pInst->sub(v0, vr);

    METHOD_OVER(1, 1);

    ARG(double, 0);

    hr = pInst->sub(v0, vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_multiply(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.multiply");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Ciphertext_base>, 0);

    hr = pInst->multiply(v0, vr);

    METHOD_OVER(1, 1);

    ARG(double, 0);

    hr = pInst->multiply(v0, vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_negate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.negate");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->negate(vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_square(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.square");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->square(vr);

    METHOD_RETURN();
}

inline void Ciphertext_base::s_relinearize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("Ciphertext.relinearize");
    METHOD_INSTANCE(Ciphertext_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->relinearize(vr);

    METHOD_RETURN();
}
}

#endif
