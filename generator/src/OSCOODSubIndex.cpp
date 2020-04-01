/**
 * @brief OSCOODSubIndex class implementation 
 * 
 * @file OSCOODSubIndex.hpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODSubIndex.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODSubIndex class implementation ----------------- */
/* Constructors */
OSCOODSubIndex::OSCOODSubIndex() :
    OSCOODObject()
{
    /* Empty */
}
OSCOODSubIndex::OSCOODSubIndex(const uint16_t &pIndex, const uint8_t &pSubIndex) :
    OSCOODObject(),
    mIndex(pIndex),
    mSubIndex(pSubIndex)
{
    /* Empty */
}

/* Destructors */
OSCOODSubIndex::~OSCOODSubIndex() {
    /* Empty */
}

/* Getters */
uint16_t OSCOODSubIndex::index(void) const {
    return mIndex;
}

uint8_t OSCOODSubIndex::subIndex(void) const {
    return mSubIndex;
}

/* Setters */
void OSCOODSubIndex::setIndex(const uint16_t &pIndex) {
    mIndex = pIndex;
}

void OSCOODSubIndex::setSubIndex(const uint8_t &pSubIndex) {
    mSubIndex = pSubIndex;
}
