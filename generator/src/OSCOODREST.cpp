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

#include "EDSTools.hpp"

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

/* Helper functions ------------------------------------ */
static void split(const std::string &pStr, const char pDelim, std::vector<std::string> &pWords) {
    size_t lPos = 0U, lOldPos = 0U;
    while(std::string::npos != lPos) {
        std::string lSub;

        /* Save the old position in the string */
        lOldPos = lPos;

        /* Find the position of the next '\n' */
        lPos = pStr.find(pDelim, lPos);

        /* Extract the substring (lSub) */
        lSub = pStr.substr(lOldPos, lPos - lOldPos);

        if(std::string::npos != lPos) {
            ++lPos;
        };

        if(lSub.empty()) {
            continue;
        }

        pWords.push_back(lSub);
    }
}

static std::vector<std::string> split(const std::string &pStr, char pDelim) {
    std::vector<std::string> lWords;

    split(pStr, pDelim, lWords);

    return lWords;
}

static HttpStatus checkPath(const std::string &lExpectedBasePath, const std::string &pPath) {
    std::string lTempStr = "";
    if(lExpectedBasePath.size() > pPath.size()) {
        std::cout << "[ERROR] <checkPath> Wrong base path " << lTempStr << std::endl;

        return HttpStatus::BAD_REQUEST;
    }

    lTempStr = pPath.substr(lExpectedBasePath.size());
    if(lExpectedBasePath == lTempStr) {
        std::cout << "[ERROR] <checkPath> Wrong base path " << lTempStr << std::endl;

        return HttpStatus::BAD_REQUEST;
    }

    return HttpStatus::OK;
}

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
    
    std::cout << "[ERROR] <OSCOODREST::OSCOOD_GET> Got path : " << pPath << std::endl;
    const std::string lBasePath = "/OSCO-OD-Gen";

    if(HttpStatus::OK != checkPath(lBasePath, pPath)) {
        std::cout << "[ERROR] <OSCOODREST::OSCOOD_GET> checkPath failed" << std::endl;
        return HttpStatus::BAD_REQUEST;
    }

    std::vector<std::string> lSubPathSections = split(pPath, '/');
    std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> Path subsections (" << lSubPathSections.size() << "): ";
    for(const auto &lElmt : lSubPathSections) {
        std::cout << lElmt << ", ";
    }
    std::cout << std::endl;

    const size_t lDepth = lSubPathSections.size();

    if(1U == lDepth) {
        /* Got just "/base-path" */
        /* Send OSCO-OD-Gen back end information 
         * Possible fields : 
         * - Version
         * - Executable name
         */
        return HttpStatus::NOT_IMPLEMENTED;
    }

    /* Get OSCOODREST instance */
    OSCOODREST * const lRESTServer = OSCOODREST::instance();

    /* Declare string to hold JSON data */
    std::string lJSON = "";

    /* Now analyse the path */
    const OSCOOD *lOD = nullptr;
    if(2U <= lDepth) {
        /* Search OD name */
        const std::string lRequestedODName = lSubPathSections.at(1U);
        try {
            lOD = lRESTServer->ODs().at(lRequestedODName);
        } catch (const std::exception &e) {
            return HttpStatus::NOT_FOUND;
        }

        /* If there is only an OD's name, send whole OD */
        if(2U == lDepth) {
            /* Get the Object dictionary JSON */
            lJSON = JSONFactory::OSCOODToJSON(*lOD);
            pOut = lJSON + "\r\n";
            return HttpStatus::OK;
        }
    }

    const OSCOODIndex *lIndex = nullptr;
    if(3U <= lDepth) {
        /* Depth 3 is Index */
        std::string lRequestedIndex = lSubPathSections.at(2U);
        uint16_t lRequestedIndexInt = 0U;

        /* Is the requested index valid ? */
        (void)remove0xPrefix(lRequestedIndex);
        if(!isIndexSection(lRequestedIndex, &lRequestedIndexInt)) {
            return HttpStatus::BAD_REQUEST;
        }

        /* Does the requested index exist ? */
        try {
            lIndex = lOD->indexes().at(lRequestedIndexInt);
        } catch (const std::exception &e) {
            return HttpStatus::NOT_FOUND;
        }

        if(3U == lDepth) {
            /* Get the index JSON */
            lJSON = JSONFactory::OSCOODIndexToJSON(*lIndex);
            pOut = lJSON + "\r\n";
            return HttpStatus::OK;
        }
    }

    const OSCOODSubIndex *lSubIndex = nullptr;
    if((4U == lDepth)) {
        /* Depth 4 is SubIndex */
        std::string lRequestedSubIndex = lSubPathSections.at(3U);
        uint8_t lRequestedSubIndexInt = 0U;

        std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> Is the requested subindex (" << lRequestedSubIndex << ") valid ?" << std::endl;

        /* Is the requested subindex valid ? */
        if(!hexStrToUInt8(lRequestedSubIndex, lRequestedSubIndexInt)) {
            return HttpStatus::BAD_REQUEST;
        }

        std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> Does the requested subindex (" << (uint16_t)lRequestedSubIndexInt << ") exist ?" << std::endl;

        /* Does the requested subindex exist ? */
        try {
            lSubIndex = lIndex->subIndexes().at(lRequestedSubIndexInt);
        } catch (const std::exception &e) {
            return HttpStatus::NOT_FOUND;
        }

        std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> Get the subindex JSON" << std::endl;

        /* Get the subindex JSON */
        lJSON = JSONFactory::OSCOODSubIndexToJSON(*lSubIndex);
        pOut = lJSON + "\r\n";

        std::cout << "[DEBUG] <OSCOODREST::OSCOOD_GET> Subindex JSON : " << pOut << std::endl;

        return HttpStatus::OK;
    }

    return HttpStatus::BAD_REQUEST;
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
