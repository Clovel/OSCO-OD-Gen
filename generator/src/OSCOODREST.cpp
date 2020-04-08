/**
 * @brief OSCOODREST class implementation
 * 
 * @file OSCOODREST.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODREST.hpp"
#include "OSCOOD.hpp"
#include "OSCOODIndex.hpp"
#include "OSCOODSubIndex.hpp"

#include "RESTServer.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/* C++ system */
#include <map>
#include <vector>
#include <iostream>

/* C System */
#include <cstdint>
#include <cstring>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* OSCOODREST class implemetation ---------------------- */

/* Constructors */
OSCOODREST::OSCOODREST(const std::string &pAddr, const std::string pPort, const std::string &pPath) :
    RESTServer(pAddr, pPort, pPath)
{
    /* Empty */
    setGetCallback(OSCOOD_GET);
    setPostCallback(OSCOOD_POST);
    setPutCallback(OSCOOD_PUT);
    setDelCallback(OSCOOD_DEL);
}

/* Destructors */
OSCOODREST::~OSCOODREST() {
    /* Empty */
}

/* Get singleton */
OSCOODREST &OSCOODREST::instance(const std::string &pAddr, const std::string pPort, const std::string &pPath) {
    static OSCOODREST sSingleton(pAddr, pPort, pPath);
    return sSingleton;
}

/* Getters */
std::map<std::string, OSCOOD *> OSCOODREST::ODs(void) const {
    return mObjectDictionaries;
}
OSCOOD *OSCOODREST::OD(const std::string &pName) const {
    try {
        return mObjectDictionaries.at(pName);
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] <OSCOODREST::OD> Object dictionary \"" << pName << "\" not found" << std::endl;
        return nullptr;
    }
}

/* Setters */
bool OSCOODREST::addOD(OSCOOD &pOD) {
    try {
        /* Does the OD already exist ? */
        (void)mObjectDictionaries.at(pOD.name());
    } catch (const std::exception &e) {
        /* It does not */
        (void)mObjectDictionaries.insert(std::pair<std::string, OSCOOD *>(pOD.name(), &pOD));

        return true;
    }

    return false;
}

bool OSCOODREST::addOD(OSCOOD * const pOD) {
    if(nullptr == pOD) {
        std::cerr << "[ERROR] <OSCOODREST::addOD> OD argument ptr is nullptr" << std::endl;
        return false;
    }
 
    return addOD(*pOD);
}

/* REST Callbacks */
HttpStatus OSCOODREST::OSCOOD_GET(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut) {
    (void)pQueries;

    /* Create a JSON Document. It is the root of the JSON string */
    rapidjson::Document lDoc; /* lDoc has type Null for now */
    lDoc.SetObject(); /* lDoc is no longer of type Null, but of type Object */

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAllocator = lDoc.GetAllocator();

    /* Add members to the document */
    lDoc.AddMember("Hello", "World", lAllocator);

    rapidjson::Value lVal;
    lVal.SetString(pPath.c_str(), pPath.size(), lAllocator);
    lDoc.AddMember("Path", lVal, lAllocator);

    /* Create a value */
    // rapidjson::Value lVal;
    // if(0U < pQueries.size()) {
    //     lVal.SetString(pQueries.at(0U).c_str(), pQueries.at(0U).size(), lDoc.GetAllocator());
    // } else {
    //     lVal.SetString("Toto fait du ski", std::strlen("Toto fait du ski"), lDoc.GetAllocator());
    // }

    rapidjson::StringBuffer lStrBuf;
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    lDoc.Accept(lWriter);

    std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> JSON : " << lStrBuf.GetString() << std::endl;

    pOut = std::string(lStrBuf.GetString()) + "\r\n";

    return HttpStatus::OK;
}

HttpStatus OSCOODREST::OSCOOD_POST(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut) {
    (void)pPath;
    (void)pQueries;
    (void)pOut;
    
    /* TODO */

    return HttpStatus::NOT_IMPLEMENTED;
}

HttpStatus OSCOODREST::OSCOOD_PUT(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut) {
    (void)pPath;
    (void)pQueries;
    (void)pOut;
    
    /* TODO */

    return HttpStatus::NOT_IMPLEMENTED;
}

HttpStatus OSCOODREST::OSCOOD_DEL(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut) {
    (void)pPath;
    (void)pQueries;
    (void)pOut;
    
    /* TODO */

    return HttpStatus::NOT_IMPLEMENTED;
}
