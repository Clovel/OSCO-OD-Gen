/**
 * @brief RESTServer class implementation
 * 
 * @file RESTServer.cpp
 */

/* Includes -------------------------------------------- */
#include "RESTServer.hpp"

/* C++ system */
#include <iostream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* RESTServer class implementation --------------------- */
/* Contructors */
RESTServer::RESTServer() {
    /* Empty */
}

RESTServer::RESTServer(utility::string_t pURL) : mListener(pURL)
{
    std::function<void(web::http::http_request)> lGetFct = &RESTServer::handleGet;
    mListener.support(web::http::methods::GET, lGetFct);

    std::function<void(web::http::http_request)> lPutFct = &RESTServer::handlePut;
    mListener.support(web::http::methods::PUT, lPutFct);

    std::function<void(web::http::http_request)> lPostFct = &RESTServer::handlePost;
    mListener.support(web::http::methods::POST, lPostFct);

    std::function<void(web::http::http_request)> lDelFct = &RESTServer::handleDelete;
    mListener.support(web::http::methods::DEL, lDelFct);
}

void RESTServer::handleGet(web::http::http_request pMsg) {
    std::cout << "[INFO ] <RESTServer::handleGet> Msg : " << std::endl << pMsg.to_string() << std::endl;
    std::cout << "[INFO ] <RESTServer::handleGet> Relative URI : " << std::endl << pMsg.relative_uri().to_string() << std::endl;
    std::cout << "[INFO ] <RESTServer::handleGet> Decoded relative URI : " << std::endl << web::uri::decode(pMsg.relative_uri().path()) << std::endl;

    std::cout << "[DEBUG] <RESTServer::handleGet> pMsg.relative_uri().path() = " << pMsg.relative_uri().path() << std::endl;
    std::cout << "[DEBUG] <RESTServer::handleGet> Decoded pMsg.relative_uri().path() = " << web::uri::decode(pMsg.relative_uri().path()) << std::endl;
    auto lPaths = web::uri::split_path(web::uri::decode(pMsg.relative_uri().path()));
    if(lPaths.empty()) {
        std::cout << "[DEBUG] <RESTServer::handleGet> lPaths is empty" << std::endl;
        // pMsg.reply(web::http::status_codes::OK);
        // return;
    } else {
        for(auto lIt1 = lPaths.begin(); lIt1 != lPaths.end(); lIt1++) {
            std::cout << U("Path") << U(" ") << *lIt1 << std::endl;
        }
    }

    std::cout << "[DEBUG] <RESTServer::handleGet> pMsg.relative_uri().query() = " << pMsg.relative_uri().query() << std::endl;
    std::cout << "[DEBUG] <RESTServer::handleGet> Decoded pMsg.relative_uri().query() = " << web::uri::decode(pMsg.relative_uri().query()) << std::endl;
#if 0
    auto lQuery = web::uri::split_query(web::uri::decode(pMsg.relative_uri().query()));
    if(lQuery.empty()) {
        std::cout << "[DEBUG] <RESTServer::handleGet> lQuery is empty" << std::endl;
        pMsg.reply(web::http::status_codes::OK);
        return;
    } else {
        for(auto lIt2 = lQuery.begin(); lIt2 != lQuery.end(); lIt2++) {
            std::cout << U("Query") << U(" ") << lIt2->second << std::endl;
        }
    }

    auto lQueryLtr = lQuery.find(U("request"));
    std::cout << U("lQueryLtr") << U(" ") << lQueryLtr->first << std::endl;
    utility::string_t lRequest = lQueryLtr->second;
    std::cout << U("Request") << U(" ") << lRequest << std::endl;
#else
    utility::string_t lRequest = web::uri::decode(pMsg.relative_uri().query());
#endif

    if(U("get_developers") == lRequest) {
        /* Build JSON */
        web::json::value lResult = web::json::value::object();
        lResult[U("name")] = web::json::value::string(U("Clovis Durand"));
        lResult[U("age")] = web::json::value::string(U("24"));

        /* Serialize JSON */
        utility::string_t lResponse = lResult.serialize();
        std::cout << "[DEBUG] <RESTServer::handleGet> Response is : " << std::endl << lResponse << std::endl;

        pMsg.reply(web::http::status_codes::OK, lResult);
        return;
    }

    pMsg.reply(web::http::status_codes::OK);
}

void RESTServer::handlePut(web::http::http_request pMsg) {
    std::cout << pMsg.to_string() << std::endl;
    pMsg.reply(web::http::status_codes::OK);
}

void RESTServer::handlePost(web::http::http_request pMsg) {
    std::cout << pMsg.to_string() << std::endl;
    pMsg.reply(web::http::status_codes::OK);
}

void RESTServer::handleDelete(web::http::http_request pMsg) {
    std::cout << pMsg.to_string() << std::endl;
    pMsg.reply(web::http::status_codes::OK);
}
