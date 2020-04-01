/**
 * @brief OSCOODIndex class implementation 
 * 
 * @file OSCOODIndex.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODIndex.hpp"
#include "OSCOODSubIndex.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODIndex class implementation -------------------- */
/* Constructors */
OSCOODIndex::OSCOODIndex() : 
    OSCOODObject()
{
    /* Empty */
}
OSCOODIndex::OSCOODIndex(const uint16_t &pIndex) : 
    OSCOODObject(),
    mIndex(pIndex)
{
    /* Empty */
}

/* Destructors */
OSCOODIndex::~OSCOODIndex() {
    /* Empty */
}

/* Getters */
uint16_t OSCOODIndex::index(void) const {
    return mIndex;
}

std::map<uint8_t, OSCOODSubIndex *> OSCOODIndex::subIndexes(void) const {
    return mSubObjects;
}

/* Setters */
void OSCOODIndex::setIndex(const uint16_t &pIndex) {
    mIndex = pIndex;
}

bool OSCOODIndex::addSubIndex(OSCOODSubIndex *pSubIndex) {
    /* Check if the subindex's index is the same as the index of this object */
    if(pSubIndex->index() != mIndex) {
        return false;
    }

    /* Check if the subindex already exists */
    for(const auto &lSubIdx : mSubObjects) {
        if(pSubIndex->subIndex() == lSubIdx.second->subIndex()) {
            return false;
        }
    }

    /* Add the subindex */
    if(mSubObjects.insert(std::pair<uint8_t, OSCOODSubIndex *>(pSubIndex->subIndex(), pSubIndex)).second) {
        return true;
    } else return false;
}

bool OSCOODIndex::removeSubIndex(const OSCOODSubIndex * const pSubIndex) {
    /* Check if the subindex's index is the same as the index of this object */
    if(pSubIndex->index() != mIndex) {
        return false;
    }

    return removeSubIndex(pSubIndex->subIndex());
}

bool OSCOODIndex::removeSubIndex(const uint8_t &pSubIndex) {
    /* Check if the subindex exists */
    for(const auto &lSubIdx : mSubObjects) {
        if(pSubIndex == lSubIdx.second->subIndex()) {
            if(0U == mSubObjects.erase(pSubIndex)) {
                return false;
            } else return true;
        }
    }

    /* Subindex was not found */
    return false;
}
