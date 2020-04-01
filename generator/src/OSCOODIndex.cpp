/**
 * @brief OSCOODIndex class implementation 
 * 
 * @file OSCOODIndex.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODIndex.hpp"

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

/* Setters */
void OSCOODIndex::setIndex(const uint16_t &pIndex) {
    mIndex = pIndex;
}
