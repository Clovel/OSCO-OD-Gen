/**
 * @brief HTTPRequest class
 * 
 * @file HTTPRequest.hpp
 */

#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#endif /* HTTPREQUEST_HPP */

/* Includes -------------------------------------------- */
/* C++ system */
#include <exception>
#include <string>
#include <vector>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */
typedef enum _httpVersion {
    HTTP_VERSION_UNKNOWN = 0U,
    HTTP_VERSION_1_0,
    HTTP_VERSION_1_1,
    HTTP_VERSION_2_0
} httpVersion_t;

typedef enum _httpMethods {
    HTTP_METHOD_UNKNOWN = 0U,
    HTTP_METHOD_GET,
    HTTP_METHOD_HEAD,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_DELETE,
    HTTP_METHOD_CONNECT,
    HTTP_METHOD_OPTIONS,
    HTTP_METHOD_TRACE,
    HTTP_METHOD_PATCH
} httpMethod_t;

typedef std::vector<std::string> httpBody_t;

/* Forward declarations -------------------------------- */

/* HTTPRequest exception ------------------------------- */
class HTTPRequestException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "HTTPRequest exception occured !";
    }
};

/* HTTPRequest class ----------------------------------- */
class HTTPRequest {
    public:
        /* Contructors */
        HTTPRequest(const std::string &pMsg);

        /* Destructor */
        virtual ~HTTPRequest();

        /* Getters */
        std::string     msg(void) const;
        std::string     methodStr(void) const;
        httpMethod_t    method(void) const;
        std::string     httpVersionStr(void) const;
        httpVersion_t   httpVersion(void) const;
        std::string     host(void) const;
        std::string     URL(void) const;
        std::string     userAgent(void) const;
        std::string     accept(void) const;
        std::string     headers(void) const;
        std::string     URI(void) const;
        std::string     query(void) const;
        httpBody_t      body(void) const;
        std::string     payload(void) const;

        /* Setters */
        /* TODO */
        // void setMsg(const std::string &pMsg);
        // void setMethodStr(const std::string &pMsg);
        // void setHTTPVersionStr(const std::string &pMsg);
        // void setHeaders(const std::string &pMsg);
        // void setURI(const std::string &pMsg);
        // void setHost(const std::string &pMsg);
        // void setURL(const std::string &pMsg);
        // void setQuery(const std::string &pMsg);

    protected:
    private:
        /* Request contents */
        std::string mMsg;               /**< Raw message received */
        std::string mMethodStr;         /**< HTTP method */
        std::string mHTTPVersionStr;    /**< HTTP Version */
        std::string mURL;               /**< HTTP URL */
        std::string mHost;              /**< HTTP Host */
        std::string mUserAgent;         /**< HTTP Client user agent */
        std::string mAccept;            /**< HTTP Accept field */
        std::string mHeaders;           /**< HTTP Headers */
        std::string mURI;               /**< HTTP URI */
        std::string mQuery;             /**< HTTP Query */
        httpBody_t  mBody;              /**< HTTP Body */
        std::string mPayload;           /**< HTTP payload */
};
