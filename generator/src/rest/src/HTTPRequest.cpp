/**
 * @brief HTTPRequest class implementation
 * 
 * @file HTTPRequest.cpp
 */


/* Includes -------------------------------------------- */
#include "HTTPRequest.hpp"

/* C++ System */
#include <iostream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Helper functions ------------------------------------ */
static std::string toStr(const httpVersion_t &pVersion) {
    switch(pVersion) {
        case HTTP_VERSION_1_0:
            return "HTTP/1.0";
        case HTTP_VERSION_1_1:
            return "HTTP/1.1";
        case HTTP_VERSION_2_0:
            return "HTTP/2.0";
        default:
            std::cerr << "[ERROR] toStr<httpVersion_t> Unknown HTTP version = " << pVersion << std::endl;
            return "";
    }
}

static std::string toStr(const httpMethod_t &pMethod) {
    switch(pMethod) {
        case HTTP_METHOD_GET:
            return "GET";
        case HTTP_METHOD_HEAD:
            return "HEAD";
        case HTTP_METHOD_POST:
            return "POST";
        case HTTP_METHOD_PUT:
            return "PUT";
        case HTTP_METHOD_DELETE:
            return "DELETE";
        case HTTP_METHOD_CONNECT:
            return "CONNECT";
        case HTTP_METHOD_OPTIONS:
            return "OPTIONS";
        case HTTP_METHOD_TRACE:
            return "TRACE";
        case HTTP_METHOD_PATCH:
            return "PATCH";
        default:
            std::cerr << "[ERROR] toStr<httpVersion_t> Unknown HTTP method = " << pMethod << std::endl;
            return "";
    }
}

static httpVersion_t strToHTTPVersion(const std::string &pStr) {
    if (pStr == toStr(HTTP_VERSION_1_0)) {
        return HTTP_VERSION_1_0;
    } else if (pStr == toStr(HTTP_VERSION_1_1)) {
        return HTTP_VERSION_1_1;
    } else if (pStr == toStr(HTTP_VERSION_2_0)) {
        return HTTP_VERSION_2_0;
    } else {
        std::cerr << "[ERROR] <strToHTTPVersion> Unknown HTTP version = " << pStr << std::endl;
        return HTTP_VERSION_UNKNOWN;
    }
}

static httpMethod_t strToHTTPMethod(const std::string &pStr) {
    if (pStr == toStr(HTTP_METHOD_GET)) {
        return HTTP_METHOD_GET;
    } else if (pStr == toStr(HTTP_METHOD_HEAD)) {
        return HTTP_METHOD_HEAD;
    } else if (pStr == toStr(HTTP_METHOD_POST)) {
        return HTTP_METHOD_POST;
    } else if (pStr == toStr(HTTP_METHOD_PUT)) {
        return HTTP_METHOD_PUT;
    } else if (pStr == toStr(HTTP_METHOD_DELETE)) {
        return HTTP_METHOD_DELETE;
    } else if (pStr == toStr(HTTP_METHOD_TRACE)) {
        return HTTP_METHOD_TRACE;
    } else if (pStr == toStr(HTTP_METHOD_OPTIONS)) {
        return HTTP_METHOD_OPTIONS;
    } else if (pStr == toStr(HTTP_METHOD_CONNECT)) {
        return HTTP_METHOD_CONNECT;
    } else if (pStr == toStr(HTTP_METHOD_PATCH)) {
        return HTTP_METHOD_PATCH;
    } else {
        std::cerr << "[ERROR] <strToHTTPMethod> Unknown HTTP method = " << pStr << std::endl;
        return HTTP_METHOD_UNKNOWN;
    }
}


/* HTTPRequest class implementation -------------------- */
HTTPRequest::HTTPRequest(const std::string &pMsg) :
    mMsg(pMsg)
{
    /* If the argument is empty, throw exception */
    if(pMsg.empty()) {
        std::cerr << "[ERROR] <HTTPRequest::HTTPRequest> Empty argument" << std::endl;
        throw HTTPRequestException();
    }

    /* Get the method */
    size_t lPos1 = 0;
    size_t lPos2 = mMsg.find(' ');
    std::cout << "[DEBUG] Method : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mMethodStr = mMsg.substr(lPos1, lPos2 - lPos1);

    /* Get the URL */
    lPos1 = lPos2 + 1;
    lPos2 = mMsg.find(' ', lPos1);
    std::cout << "[DEBUG] URL : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mURL = mMsg.substr(lPos1, lPos2 - lPos1);

    /* Get the HTTP version */
    lPos1 = lPos2 + 1;
    lPos2 = mMsg.find('\n', lPos1);
    std::cout << "[DEBUG] Host : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mHTTPVersionStr = mMsg.substr(lPos1, lPos2 - lPos1);

    /* Get the host */
    lPos1 = lPos2 + 1;
    lPos1 = mMsg.find("Host: ", lPos1) + std::string("Host: ").size();
    lPos2 = mMsg.find('\n', lPos1);
    std::cout << "[DEBUG] Host : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mHost = mMsg.substr(lPos1, lPos2 - lPos1);

    /* Get the User-Agent */
    lPos1 = lPos2 + 1;
    lPos1 = mMsg.find("User-Agent: ", lPos1) + std::string("User-Agent: ").size();
    lPos2 = mMsg.find('\n', lPos1);
    std::cout << "[DEBUG] Host : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mUserAgent = mMsg.substr(lPos1, lPos2 - lPos1);

    /* Get the Accept field */
    lPos1 = lPos2 + 1;
    lPos1 = mMsg.find("Accept: ", lPos1) + std::string("Accept: ").size();
    lPos2 = mMsg.find('\n', lPos1);
    std::cout << "[DEBUG] Host : lPos1 : " << lPos1 << ", lPos2 : " << lPos2 << std::endl;
    mAccept = mMsg.substr(lPos1, lPos2 - lPos1);
}

HTTPRequest::~HTTPRequest() {
    /* Empty */
}

/* Getters */
std::string HTTPRequest::msg(void) const {
    return mMsg;
}

std::string HTTPRequest::methodStr(void) const {
    return mMethodStr;
}

httpMethod_t HTTPRequest::method(void) const {
    return strToHTTPMethod(mMethodStr);
}

std::string HTTPRequest::httpVersionStr(void) const {
    return mHTTPVersionStr;
}

httpVersion_t HTTPRequest::httpVersion(void) const {
    return strToHTTPVersion(mHTTPVersionStr);
}

std::string HTTPRequest::URL(void) const {
    return mURL;
}

std::string HTTPRequest::host(void) const {
    return mHost;
}

std::string HTTPRequest::userAgent(void) const {
    return mUserAgent;
}

std::string HTTPRequest::accept(void) const {
    return mAccept;
}

std::string HTTPRequest::headers(void) const {
    return mHeaders;
}

std::string HTTPRequest::URI(void) const {
    return mURI;
}

std::string HTTPRequest::query(void) const {
    return mQuery;
}

httpBody_t HTTPRequest::body(void) const {
    return mBody;
}

std::string HTTPRequest::payload(void) const {
    return mPayload;
}

/* Setters */
