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

#include "JSONFactory.hpp"

/* C++ system */
#include <map>
#include <vector>
#include <iostream>

/* C System */
#include <cstdint>
#include <cstring>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Static variables ------------------------------------ */
static OSCOODREST *sSingleton = nullptr;

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
OSCOODREST *OSCOODREST::createInstance(const std::string &pAddr, const std::string pPort, const std::string &pPath) {
    if(nullptr == sSingleton) {
        sSingleton = new OSCOODREST(pAddr, pPort, pPath);
    } else {
        (void)pAddr;
        (void)pPort;
        (void)pPath;
    }

    return sSingleton;
}

OSCOODREST *OSCOODREST::instance(void) {
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
    (void)pPath;

    /* Get OSCOODREST instance */
    OSCOODREST * const lRESTServer = OSCOODREST::instance();

    /* Get the Object dictionary JSON */
    const std::string lODJSON = JSONFactory::OSCOODToJSON(*lRESTServer->ODs().at("IO Example"));

    //std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> JSON : " << lODJSON << std::endl;

    pOut = lODJSON + "\r\n";

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
