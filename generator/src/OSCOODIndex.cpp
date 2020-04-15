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

/* C++ system */
#include <iostream>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODIndex class implementation -------------------- */
/* Constructors */
OSCOODIndex::OSCOODIndex() : 
    OSCOODObject(),
    mIndex(0x0000U)
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
    for(auto &lSubObject : mSubObjects) {
        if(nullptr != lSubObject.second) {
            delete lSubObject.second;
            lSubObject.second = nullptr;
        }
    }
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
        std::cerr << "[ERROR] <OSCOODIndex::addSubIndex> SubIndex's index does not match this index" << std::endl;
        return false;
    }

    /* Check if the subindex already exists */
    for(const auto &lSubIdx : mSubObjects) {
        if(pSubIndex->subIndex() == lSubIdx.second->subIndex()) {
            std::cerr << "[ERROR] <OSCOODIndex::addSubIndex> SubIndex already exists" << std::endl;
            return false;
        }
    }

    /* Add the subindex */
    if(mSubObjects.insert(std::pair<uint8_t, OSCOODSubIndex *>(pSubIndex->subIndex(), pSubIndex)).second) {
        return true;
    } else {
        std::cerr << "[ERROR] <OSCOODIndex::addSubIndex> Failed to insert subindex to map" << std::endl;
        return false;
    }
}

bool OSCOODIndex::removeSubIndex(const OSCOODSubIndex * const pSubIndex) {
    /* Check if the subindex's index is the same as the index of this object */
    if(pSubIndex->index() != mIndex) {
        std::cerr << "[ERROR] <OSCOODIndex::removeSubIndex> SubIndex's index does not match this index" << std::endl;
        return false;
    }

    return removeSubIndex(pSubIndex->subIndex());
}

bool OSCOODIndex::removeSubIndex(const uint8_t &pSubIndex) {
    /* Check if the subindex exists */
    for(const auto &lSubIdx : mSubObjects) {
        if(pSubIndex == lSubIdx.second->subIndex()) {
            if(0U == mSubObjects.erase(pSubIndex)) {
                std::cerr << "[ERROR] <OSCOODIndex::removeSubIndex> Failed to erase subindex from map" << std::endl;
                return false;
            } else return true;
        }
    }

    /* Subindex was not found */
    return false;
}
