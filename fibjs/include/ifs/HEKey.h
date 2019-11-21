/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _HEKey_base_H_
#define _HEKey_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs {

class Buffer_base;
class Ciphertext_base;

class HEKey_base : public object_base {
    DECLARE_CLASS(HEKey_base);

public:
    // HEKey_base
    static result_t _new(obj_ptr<HEKey_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    static result_t _new(int32_t scheme_type, int32_t poly_modulus_degree, int32_t plain_modulus, obj_ptr<HEKey_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    static result_t _new(int32_t scheme_type, int32_t poly_modulus_degree, int32_t scale, v8::Local<v8::Array> coeff_modulus, obj_ptr<HEKey_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t get_scheme_type(exlib::string& retVal) = 0;
    virtual result_t get_poly_modulus_degree(int32_t& retVal) = 0;
    virtual result_t get_plain_modulus(int32_t& retVal) = 0;
    virtual result_t get_scale(int32_t& retVal) = 0;
    virtual result_t get_coeff_modulus(v8::Local<v8::Array>& retVal) = 0;
    virtual result_t genKey() = 0;
    virtual result_t importKey(Buffer_base* priKey) = 0;
    virtual result_t exportKey(obj_ptr<Buffer_base>& retVal) = 0;
    virtual result_t encrypt(double number, obj_ptr<Ciphertext_base>& retVal) = 0;
    virtual result_t decrypt(Ciphertext_base* ciphertext, double& retVal) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_scheme_type(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_poly_modulus_degree(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_plain_modulus(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_scale(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_coeff_modulus(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_genKey(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_importKey(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_exportKey(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_encrypt(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_decrypt(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

#include "ifs/Buffer.h"
#include "ifs/Ciphertext.h"

namespace fibjs {
inline ClassInfo& HEKey_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "genKey", s_genKey, false },
        { "importKey", s_importKey, false },
        { "exportKey", s_exportKey, false },
        { "encrypt", s_encrypt, false },
        { "decrypt", s_decrypt, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "scheme_type", s_get_scheme_type, block_set, false },
        { "poly_modulus_degree", s_get_poly_modulus_degree, block_set, false },
        { "plain_modulus", s_get_plain_modulus, block_set, false },
        { "scale", s_get_scale, block_set, false },
        { "coeff_modulus", s_get_coeff_modulus, block_set, false }
    };

    static ClassData s_cd = {
        "HEKey", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void HEKey_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void HEKey_base::__new(const T& args)
{
    obj_ptr<HEKey_base> vr;

    METHOD_NAME("new HEKey()");
    CONSTRUCT_ENTER();

    METHOD_OVER(0, 0);

    hr = _new(vr, args.This());

    METHOD_OVER(3, 0);

    OPT_ARG(int32_t, 0, 1);
    OPT_ARG(int32_t, 1, 4096);
    OPT_ARG(int32_t, 2, 1024);

    hr = _new(v0, v1, v2, vr, args.This());

    METHOD_OVER(4, 1);

    OPT_ARG(int32_t, 0, 2);
    OPT_ARG(int32_t, 1, 4096);
    OPT_ARG(int32_t, 2, 60);
    ARG(v8::Local<v8::Array>, 3);

    hr = _new(v0, v1, v2, v3, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void HEKey_base::s_get_scheme_type(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_NAME("HEKey.scheme_type");
    METHOD_INSTANCE(HEKey_base);
    PROPERTY_ENTER();

    hr = pInst->get_scheme_type(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_get_poly_modulus_degree(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("HEKey.poly_modulus_degree");
    METHOD_INSTANCE(HEKey_base);
    PROPERTY_ENTER();

    hr = pInst->get_poly_modulus_degree(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_get_plain_modulus(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("HEKey.plain_modulus");
    METHOD_INSTANCE(HEKey_base);
    PROPERTY_ENTER();

    hr = pInst->get_plain_modulus(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_get_scale(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("HEKey.scale");
    METHOD_INSTANCE(HEKey_base);
    PROPERTY_ENTER();

    hr = pInst->get_scale(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_get_coeff_modulus(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    v8::Local<v8::Array> vr;

    METHOD_NAME("HEKey.coeff_modulus");
    METHOD_INSTANCE(HEKey_base);
    PROPERTY_ENTER();

    hr = pInst->get_coeff_modulus(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_genKey(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("HEKey.genKey");
    METHOD_INSTANCE(HEKey_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->genKey();

    METHOD_VOID();
}

inline void HEKey_base::s_importKey(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("HEKey.importKey");
    METHOD_INSTANCE(HEKey_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Buffer_base>, 0);

    hr = pInst->importKey(v0);

    METHOD_VOID();
}

inline void HEKey_base::s_exportKey(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Buffer_base> vr;

    METHOD_NAME("HEKey.exportKey");
    METHOD_INSTANCE(HEKey_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->exportKey(vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_encrypt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Ciphertext_base> vr;

    METHOD_NAME("HEKey.encrypt");
    METHOD_INSTANCE(HEKey_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(double, 0);

    hr = pInst->encrypt(v0, vr);

    METHOD_RETURN();
}

inline void HEKey_base::s_decrypt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    double vr;

    METHOD_NAME("HEKey.decrypt");
    METHOD_INSTANCE(HEKey_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Ciphertext_base>, 0);

    hr = pInst->decrypt(v0, vr);

    METHOD_RETURN();
}
}

#endif
