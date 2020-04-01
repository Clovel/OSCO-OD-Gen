/**
 * @brief OSCOODObject class implementation
 * 
 * @file OSCOODObject.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODObject.hpp"

/* C++ system */
#include <string>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODObject class implementation ------------------- */

/* Constructors */
OSCOODObject::OSCOODObject() {
    /* Empty */
}

/* Desctructor */
OSCOODObject::~OSCOODObject() {
    /* Empty */
}

/* Getters */
uint8_t OSCOODObject::subNumber(void) const {
    return mSubNumber;
}

std::string OSCOODObject::paramName(void) const {
    return mParamName;
}

uint8_t OSCOODObject::objectType(void) const {
    return mObjectType;
}

uint8_t OSCOODObject::dataType(void) const {
    return mDataType;
}

std::string OSCOODObject::accessType(void) const {
    return mAccessType;
}

std::string OSCOODObject::defaultValue(void) const {
    return mDefaultValue;
}

std::string OSCOODObject::lowLimit(void) const {
    return mLowLimit;
}

std::string OSCOODObject::highLimit(void) const {
    return mHighLimit;
}

bool OSCOODObject::pdoMapping(void) const {
    return mPDOMapping;
}

uint32_t OSCOODObject::objFlags(void) const {
    return mObjFlags;
}
uint8_t OSCOODObject::compactSubObj(void) const {
    return mCompactSubObj;
}


/* Setters */
void OSCOODObject::setSubNumber(const uint8_t &pSubNb) {
    mSubNumber = pSubNb;
}

void OSCOODObject::setParamName(const std::string &pParamName) {
    mParamName = pParamName;
}

void OSCOODObject::setObjectType(const uint8_t &pObjType) {
    mObjectType = pObjType;
}

void OSCOODObject::setDataType(const uint8_t &pDataType) {
    mDataType = pDataType;
}

void OSCOODObject::setAccessType(const std::string &pAccessType) {
    mAccessType = pAccessType;
}

void OSCOODObject::setDefaultValue(const std::string &pDefaultValue) {
    mDefaultValue = pDefaultValue;
}

void OSCOODObject::setLowLimit(const std::string &pLowLimit) {
    mLowLimit = pLowLimit;
}

void OSCOODObject::setHighLimit(const std::string &pHighLimit) {
    mHighLimit = pHighLimit;
}

void OSCOODObject::allowPDOMapping(void) {
    mPDOMapping = true;
}

void OSCOODObject::forbidPDOMapping(void) {
    mPDOMapping = false;
}

void OSCOODObject::setObjFlags(const uint32_t &pObjFlags) {
    mObjFlags = pObjFlags;
}

void OSCOODObject::setCompactSubObj(const uint8_t &pCompactSubObj) {
    mCompactSubObj = pCompactSubObj;
}
