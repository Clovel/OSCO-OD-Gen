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

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* OSCOOD class implemetation -------------------------- */
/* Constructors */
OSCOOD::OSCOOD();

/* Destructor */
OSCOOD::~OSCOOD();

/* Getters */
std::map<uint16_t, OSCOODIndex *> OSCOOD::indexes(void) const {
    return mObjects;
}

/* Setters */
bool OSCOOD::addIndex(OSCOODIndex *pIndex) {
    /* Check if the index already exists */
    for(const auto &lIdx : mObjects) {
        if(pIndex->index() == lIdx.second->index()) {
            return false;
        }
    }

    /* Add the subindex */
    if(mObjects.insert(std::pair<uint8_t, OSCOODIndex *>(pIndex->index(), pIndex)).second) {
        return true;
    } else return false;
}

bool OSCOOD::removeIndex(const OSCOODIndex * const pIndex) {
    return removeIndex(pIndex->index());
}

bool OSCOOD::removeIndex(const uint16_t &pIndex) {
    /* Check if the index exists */
    for(const auto &lIdx : mObjects) {
        if(pIndex == lIdx.second->index()) {
            if(0U == mObjects.erase(pIndex)) {
                return false;
            } else return true;
        }
    }

    /* Index was not found */
    return false;
}
