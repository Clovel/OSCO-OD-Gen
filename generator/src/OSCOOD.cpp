/**
 * @brief OSCOOD class implemetation
 * 
 * @file OSCOOD.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOOD.hpp"
#include "OSCOODIndex.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C++ system */
#include <map>
#include <vector>
#include <iostream>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* OSCOOD class implemetation -------------------------- */
/* Constructors */
OSCOOD::OSCOOD() {
    /* Empty */
}

OSCOOD::OSCOOD(const std::map<uint16_t, OSCOODIndex *> &pObjects) :
    mObjects(pObjects)
{
    /* Empty */
}

OSCOOD::OSCOOD(const std::vector<OSCOODIndex *> &pObjects)
{
    /* Fill our objects with the given argument */
    for(const auto &lObj : pObjects) {
        if(!mObjects.insert(std::pair(lObj->index(), lObj)).second) {
            std::cerr << "[ERROR] <OSCOOD::OSCOOD> Failed to insert index to map" << std::endl;
            throw OSCOODException();
        }
    }
}

/* Destructor */
OSCOOD::~OSCOOD() {
    for(auto &lObject : mObjects) {
        if(nullptr != lObject.second) {
            delete lObject.second;
            lObject.second = nullptr;
        }
    }
}

/* Getters */
std::map<uint16_t, OSCOODIndex *> OSCOOD::indexes(void) const {
    return mObjects;
}

/* Setters */
bool OSCOOD::addIndex(OSCOODIndex *pIndex) {
    /* Check if the index already exists */
    for(const auto &lIdx : mObjects) {
        if(pIndex->index() == lIdx.second->index()) {
            std::cerr << "[ERROR] <OSCOOD::addIndex> Index already exists" << std::endl;
            return false;
        }
    }

    /* Add the subindex */
    if(mObjects.insert(std::pair<uint16_t, OSCOODIndex *>(pIndex->index(), pIndex)).second) {
        return true;
    } else {
        std::cerr << "[ERROR] <OSCOOD::addIndex> Failed to insert index to map" << std::endl;
        return false;
    }
}

bool OSCOOD::removeIndex(const OSCOODIndex * const pIndex) {
    return removeIndex(pIndex->index());
}

bool OSCOOD::removeIndex(const uint16_t &pIndex) {
    /* Check if the index exists */
    for(const auto &lIdx : mObjects) {
        if(pIndex == lIdx.second->index()) {
            if(0U == mObjects.erase(pIndex)) {
                std::cerr << "[ERROR] <OSCOOD::removeIndex> Failed to erase index from map" << std::endl;
                return false;
            } else return true;
        }
    }

    /* Index was not found */
    std::cerr << "[ERROR] <OSCOOD::removeIndex> Index not found" << std::endl;
    return false;
}
