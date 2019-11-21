/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _he_base_H_
#define _he_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs {

class HEKey_base;
class Ciphertext_base;

class he_base : public object_base {
    DECLARE_CLASS(he_base);

public:
    enum {
        _BFV = 1,
        _CKKS = 2
    };

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        Isolate* isolate = Isolate::current();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }
};
}

#include "ifs/HEKey.h"
#include "ifs/Ciphertext.h"

namespace fibjs {
inline ClassInfo& he_base::class_info()
{
    static ClassData::ClassObject s_object[] = {
        { "HEKey", HEKey_base::class_info },
        { "Ciphertext", Ciphertext_base::class_info }
    };

    static ClassData::ClassConst s_const[] = {
        { "BFV", _BFV },
        { "CKKS", _CKKS }
    };

    static ClassData s_cd = {
        "he", true, s__new, NULL,
        0, NULL, ARRAYSIZE(s_object), s_object, 0, NULL, ARRAYSIZE(s_const), s_const, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}
}

#endif
