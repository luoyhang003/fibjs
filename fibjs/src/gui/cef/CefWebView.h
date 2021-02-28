/*
 * CefWebView.h
 *
 *  Created on: Feb 24, 2021
 *      Author: lion
 */

#include "ifs/WebView.h"
#include "ifs/json.h"
#include "include/cef_client.h"

#ifndef WEBVIEW_CEF_H_
#define WEBVIEW_CEF_H_

namespace fibjs {

class CefWebView : public WebView_base,
                   public CefDevToolsMessageObserver {
public:
    CefWebView(exlib::string url, NObject* opt);
    ~CefWebView();

    EVENT_SUPPORT();

public:
    // WebView_base
    virtual result_t loadUrl(exlib::string url, AsyncEvent* ac);
    virtual result_t setHtml(exlib::string html, AsyncEvent* ac);
    virtual result_t reload(AsyncEvent* ac);
    virtual result_t goBack(AsyncEvent* ac);
    virtual result_t goForward(AsyncEvent* ac);
    virtual result_t print(int32_t mode, AsyncEvent* ac);
    virtual result_t printToPDF(exlib::string file, AsyncEvent* ac);
    virtual result_t executeJavaScript(exlib::string code, AsyncEvent* ac);
    virtual result_t executeDevToolsMethod(exlib::string method, v8::Local<v8::Object> params, Variant& retVal, AsyncEvent* ac);
    virtual result_t close(AsyncEvent* ac);
    virtual result_t postMessage(exlib::string msg, AsyncEvent* ac);
    virtual result_t get_dev(v8::Local<v8::Value>& retVal);

public:
    // CefDevToolsMessageObserver
    virtual void OnDevToolsMethodResult(CefRefPtr<CefBrowser> browser, int message_id,
        bool success, const void* result, size_t result_size);
    virtual void OnDevToolsEvent(CefRefPtr<CefBrowser> browser, const CefString& method,
        const void* params, size_t params_size);

public:
    EVENT_FUNC(open);
    EVENT_FUNC(load);
    EVENT_FUNC(move);
    EVENT_FUNC(resize);
    EVENT_FUNC(closed);
    EVENT_FUNC(message);

public:
    void AddRef() const OVERRIDE
    {
    }

    bool Release() const OVERRIDE
    {
        return false;
    }

    bool HasOneRef() const OVERRIDE
    {
        return false;
    }

    bool HasAtLeastOneRef() const OVERRIDE
    {
        return true;
    }

public:
    void open();
    void config_window();
    void clear();

public:
    CefRefPtr<CefBrowser> m_browser;

    obj_ptr<NObject> m_opt;
    exlib::string m_url;

    bool m_bDebug;
    bool m_bPopup;
    bool m_bHeadless;

private:
    class JSONValue : public object_base {
    public:
        JSONValue(exlib::string s)
            : m_json(s)
        {
        }

    public:
        // object_base
        virtual result_t valueOf(v8::Local<v8::Value>& retVal)
        {
            return json_base::decode(m_json, retVal);
        }

    private:
        exlib::string m_json;
    };

    class ac_method {
    public:
        ac_method(Variant& retVal, AsyncEvent* ac)
            : m_retVal(retVal)
            , m_ac(ac)
        {
        }

    public:
        Variant& m_retVal;
        AsyncEvent* m_ac;
    };

    int32_t m_eid;
    std::map<int32_t, ac_method> m_method;
    std::map<exlib::string, obj_ptr<EventEmitter_base>> m_domain;

    CefRefPtr<CefRegistration> m_reg;
};
}

#endif