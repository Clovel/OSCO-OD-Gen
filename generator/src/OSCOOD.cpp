/**
 * @brief OSCOOD class implemetation
 * 
 * @file OSCOOD.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOOD.hpp"
#include "OSCOODIndex.hpp"

/* C++ system */
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

/* C System */
#include <cstdint>
#include <cstring>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* OSCOOD class implemetation -------------------------- */
/* Constructors */
OSCOOD::OSCOOD() :
    mFileVersion(0U),
    mFileRevision(0U),
    mVendorNumber(0U),
    mProductNumber(0U),
    mRevisionNumber(0U),
    mBaudRate_10(false),
    mBaudRate_20(false),
    mBaudRate_50(false),
    mBaudRate_125(false),
    mBaudRate_250(false),
    mBaudRate_500(false),
    mBaudRate_800(false),
    mBaudRate_1000(false),
    mSimpleBootUpMaster(false),
    mSimpleBootUpSlave(false),
    mGranularity(0U),
    mDynamicChannelsSupported(0U),
    mGroupMessaging(false),
    mNrOfRXPDO(0U),
    mNrOfTXPDO(0U),
    mLSSSupported(false),
    mCommentLineCount(0U),
    mDummy0001(false),
    mDummy0002(false),
    mDummy0003(false),
    mDummy0004(false),
    mDummy0005(false),
    mDummy0006(false),
    mDummy0007(false)
{
    std::memset(&mCreationDateTime,     0, sizeof(mCreationDateTime));
    std::memset(&mModificationDateTime, 0, sizeof(mModificationDateTime));
}

OSCOOD::OSCOOD(const std::map<uint16_t, OSCOODIndex *> &pObjects) :
    mObjects(pObjects),
    mFileVersion(0U),
    mFileRevision(0U),
    mVendorNumber(0U),
    mProductNumber(0U),
    mRevisionNumber(0U),
    mBaudRate_10(false),
    mBaudRate_20(false),
    mBaudRate_50(false),
    mBaudRate_125(false),
    mBaudRate_250(false),
    mBaudRate_500(false),
    mBaudRate_800(false),
    mBaudRate_1000(false),
    mSimpleBootUpMaster(false),
    mSimpleBootUpSlave(false),
    mGranularity(0U),
    mDynamicChannelsSupported(0U),
    mGroupMessaging(false),
    mNrOfRXPDO(0U),
    mNrOfTXPDO(0U),
    mLSSSupported(false),
    mCommentLineCount(0U),
    mDummy0001(false),
    mDummy0002(false),
    mDummy0003(false),
    mDummy0004(false),
    mDummy0005(false),
    mDummy0006(false),
    mDummy0007(false)
{
    std::memset(&mCreationDateTime,     0, sizeof(mCreationDateTime));
    std::memset(&mModificationDateTime, 0, sizeof(mModificationDateTime));
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

std::string OSCOOD::name(void) const {
    return mName;
}

std::string OSCOOD::fileName(void) const {
    return mFileName;
}

uint8_t OSCOOD::fileVersion(void) const {
    return mFileVersion;
}

uint8_t OSCOOD::fileRevision(void) const {
    return mFileRevision;
}

std::string OSCOOD::EDSVersion(void) const {
    return mEDSVersion;
}

std::string OSCOOD::description(void) const {
    return mDesription;
}

std::string OSCOOD::creationDate(const bool &pFormat) const {
    char lDateStr[20U];
    struct tm *lDateTimeStruct = std::gmtime(&mCreationDateTime);
    if(pFormat)
        (void)strftime(lDateStr, 20U, "%d/%m/%Y", lDateTimeStruct);
    else
        (void)strftime(lDateStr, 20U, "%Y-%m-%d", lDateTimeStruct);
    return std::string(lDateStr);
}

std::string OSCOOD::creationTime(const bool &pFormat) const {
    char lTimeStr[20U];
    struct tm *lDateTimeStruct = std::gmtime(&mCreationDateTime);
    if(pFormat)
        (void)strftime(lTimeStr, 20U, "%H:%M:%S", lDateTimeStruct);
    else
        (void)strftime(lTimeStr, 20U, "%I:%M%p", lDateTimeStruct);
    return std::string(lTimeStr);
}

std::time_t OSCOOD::creationDateTime(void) const {
    return mCreationDateTime;
}

std::string OSCOOD::createdBy(void) const {
    return mCreatedBy;
}

std::string OSCOOD::modificationDate(const bool &pFormat) const {
    char lDateStr[20U];
    struct tm *lDateTimeStruct = std::gmtime(&mModificationDateTime);
    if(pFormat)
        (void)strftime(lDateStr, 20U, "%d/%m/%Y", lDateTimeStruct);
    else
        (void)strftime(lDateStr, 20U, "%Y-%m-%d", lDateTimeStruct);
    return std::string(lDateStr);
}

std::string OSCOOD::modificationTime(const bool &pFormat) const {
    char lTimeStr[20U];
    struct tm *lDateTimeStruct = std::gmtime(&mModificationDateTime);
    if(pFormat)
        (void)strftime(lTimeStr, 20U, "%H:%M:%S", lDateTimeStruct);
    else
        (void)strftime(lTimeStr, 20U, "%I:%M%p", lDateTimeStruct);
    return std::string(lTimeStr);
}

std::time_t OSCOOD::modificationDateTime(void) const {
    return mModificationDateTime;
}

std::string OSCOOD::modifiedBy(void) const {
    return mModifiedBy;
}

std::string OSCOOD::vendorName(void) const {
    return mVendorName;
}

uint32_t OSCOOD::vendorNumber(void) const {
    return mVendorNumber;
}

std::string OSCOOD::productName(void) const {
    return mProductName;
}

uint32_t OSCOOD::productNumber(void) const {
    return mProductNumber;
}

uint32_t OSCOOD::revisionNumber(void) const {
    return mRevisionNumber;
}

std::string OSCOOD::orderCode(void) const {
    return mOrderCode;
}

bool OSCOOD::baudrate10Supported(void) const {
    return mBaudRate_10;
}

bool OSCOOD::baudrate20Supported(void) const {
    return mBaudRate_20;
}

bool OSCOOD::baudrate50Supported(void) const {
    return mBaudRate_50;
}

bool OSCOOD::baudrate125Supported(void) const {
    return mBaudRate_125;
}

bool OSCOOD::baudrate250Supported(void) const {
    return mBaudRate_250;
}

bool OSCOOD::baudrate500Supported(void) const {
    return mBaudRate_500;
}

bool OSCOOD::baudrate800Supported(void) const {
    return mBaudRate_800;
}

bool OSCOOD::baudrate1000Supported(void) const {
    return mBaudRate_1000;
}

bool OSCOOD::simpleBootUpMaster(void) const {
    return mSimpleBootUpMaster;
}

bool OSCOOD::simpleBootUpSlave(void) const {
    return mSimpleBootUpSlave;
}

uint8_t OSCOOD::granularity(void) const {
    return mGranularity;
}

uint8_t OSCOOD::dynamicChannelsSupported(void) const {
    return mDynamicChannelsSupported;
}

bool OSCOOD::groupMessaging(void) const {
    return mGroupMessaging;
}

uint16_t OSCOOD::nrOfRPDOs(void) const {
    return mNrOfRXPDO;
}

uint16_t OSCOOD::nrOfTPDOs(void) const {
    return mNrOfTXPDO;
}

bool OSCOOD::LSSSupported(void) const {
    return mLSSSupported;
}

std::string OSCOOD::comments(void) const {
    return mComments;
}

std::string OSCOOD::commentLine(const uint32_t &pLine) const {
    if(mCommentLineCount <= pLine) {
        std::cerr << "[ERROR] <OSCOOD::commentLine> Line arg out of bounds (bound : " << mCommentLineCount << " <= arg : " << pLine << ")" << std::endl;
        return "[ERROR OCCURED]";
    }

    std::istringstream lISS(mComments);
    for(uint32_t i = 0U; i < mCommentLineCount; i++) {
        std::string lLine = "";
        (void)std::getline(lISS, lLine);
        if(pLine == i) {
            return lLine;
        }
    }

    /* Line not found, shouldn't happen */
    return "[ERROR OCCURED]";
}

uint32_t OSCOOD::commentLineCount(void) const {
    return mCommentLineCount;
}

bool OSCOOD::dummy0001Supported(void) const {
    return mDummy0001;
}

bool OSCOOD::dummy0002Supported(void) const {
    return mDummy0002;
}

bool OSCOOD::dummy0003Supported(void) const {
    return mDummy0003;
}

bool OSCOOD::dummy0004Supported(void) const {
    return mDummy0004;
}

bool OSCOOD::dummy0005Supported(void) const {
    return mDummy0005;
}

bool OSCOOD::dummy0006Supported(void) const {
    return mDummy0006;
}

bool OSCOOD::dummy0007Supported(void) const {
    return mDummy0007;
}

bool OSCOOD::dummySupported(const uint8_t &pDummy, bool &pSupported) const {
    switch(pDummy) {
        case 1U:
            pSupported = dummy0001Supported();
            break;
        case 2U:
            pSupported = dummy0002Supported();
            break;
        case 3U:
            pSupported = dummy0003Supported();
            break;
        case 4U:
            pSupported = dummy0004Supported();
            break;
        case 5U:
            pSupported = dummy0005Supported();
            break;
        case 6U:
            pSupported = dummy0006Supported();
            break;
        case 7U:
            pSupported = dummy0007Supported();
            break;
        default:
            std::cerr << "[ERROR] <OSCOOD::dummySupported> pDummy out of bounds" << std::endl;
            return false;
    }

    return true;
}

std::string OSCOOD::customHeader(void) const {
    return mCustomHeader;
}

std::string OSCOOD::sourceFilePath(void) const {
    return mSourceFilePath;
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

void OSCOOD::setName(const std::string &pName) {
    mName = pName;
}

void OSCOOD::setFileName(const std::string &pFileName) {
    mFileName = pFileName;
}

void OSCOOD::setFileVersion(const uint8_t &pVersion) {
    mFileVersion = pVersion;
}

void OSCOOD::setFileRevision(const uint8_t &pRevision) {
    mFileRevision = pRevision;
}

void OSCOOD::setEDSVersion(const std::string &pVersion) {
    mEDSVersion = pVersion;
}

void OSCOOD::setDescription(const std::string &pDescription) {
    mDescription = pDescription;
}

bool OSCOOD::setCreationDate(const std::string &pDate) {
    struct tm lDateTimeStruct;
    std::memset(&lDateTimeStruct, 0, sizeof(struct tm));

    /* The input string should only contain the date
     * in either the YYYY-MM-DD format
     * or the DD/MM/YYYY format.
     * 
     * Both are 10 chars long (+ 1 for the NULL terminator)
     */

    if(strptime(pDate.c_str(), "%Y-%m-%d", &lDateTimeStruct)) {
        /* Do nothing */
    } else if(strptime(pDate.c_str(), "%d/%m/%Y", &lDateTimeStruct)) {
        /* Do nothing */
    } else {
        std::cerr << "[ERROR] <OSCOOD::setCreationDate> Wrong date format" << std::endl;
        return false;
    }

    struct tm *lCreationDateTimeStruct = gmtime(&mCreationDateTime);
    if(nullptr == lCreationDateTimeStruct) {
        std::cerr << "[ERROR] <OSCOOD::setCreationDate> gmtime failed (mCreationDateTime = " << mCreationDateTime << ")" << std::endl;
        return false;
    }
    lCreationDateTimeStruct->tm_mday = lDateTimeStruct.tm_mday;
    lCreationDateTimeStruct->tm_mon  = lDateTimeStruct.tm_mon;
    lCreationDateTimeStruct->tm_year = lDateTimeStruct.tm_year;
    mCreationDateTime = mktime(lCreationDateTimeStruct);

    return true;
}

bool OSCOOD::setCreationTime(const std::string &pTime) {
    struct tm lDateTimeStruct;
    std::memset(&lDateTimeStruct, 0, sizeof(struct tm));

    /* The input string should only contain the time
     * in either the AM/PM format
     * or the 24-hour format
     */

    if(strptime(pTime.c_str(), "%I:%M%p", &lDateTimeStruct)) {
        /* Do nothing */
    } else if (strptime(pTime.c_str(), "%H:%M:%S", &lDateTimeStruct)) {
        /* Do nothing */
    } else if (strptime(pTime.c_str(), "%H:%M", &lDateTimeStruct)) {
        /* Do nothing */
    } else {
        std::cerr << "[ERROR] <OSCOOD::setCreationTime> Wrong time format" << std::endl;
        return false;
    }

    struct tm *lCreationDateTimeStruct = gmtime(&mCreationDateTime);
    if(nullptr == lCreationDateTimeStruct) {
        std::cerr << "[ERROR] <OSCOOD::setCreationTime> gmtime failed (mCreationDateTime = " << mCreationDateTime << ")" << std::endl;
        return false;
    }
    lCreationDateTimeStruct->tm_hour = lDateTimeStruct.tm_hour;
    lCreationDateTimeStruct->tm_min  = lDateTimeStruct.tm_min;
    lCreationDateTimeStruct->tm_sec  = lDateTimeStruct.tm_sec;
    mCreationDateTime = mktime(lCreationDateTimeStruct);

    return true;
}

void OSCOOD::setCreationDateTime(const std::time_t &pDateTime) {
    mCreationDateTime = pDateTime;
}

void OSCOOD::setCreatedBy(const std::string &pCreatedBy) {
    mCreatedBy = pCreatedBy;
}

bool OSCOOD::setModificationDate(const std::string &pDate) {
    struct tm lDateTimeStruct;
    std::memset(&lDateTimeStruct, 0, sizeof(struct tm));

    /* The input string should only contain the date
     * in either the YYYY-MM-DD format
     * or the DD/MM/YYYY format.
     * 
     * Both are 10 chars long (+ 1 for the NULL terminator)
     */

    if(strptime(pDate.c_str(), "%Y-%m-%d", &lDateTimeStruct)) {
        /* Do nothing */
    } else if(strptime(pDate.c_str(), "%d/%m/%Y", &lDateTimeStruct)) {
        /* Do nothing */
    } else {
        std::cerr << "[ERROR] <OSCOOD::setModificationDate> Wrong date format" << std::endl;
        return false;
    }

    struct tm *lModificationDateTimeStruct = gmtime(&mModificationDateTime);
    if(nullptr == lModificationDateTimeStruct) {
        std::cerr << "[ERROR] <OSCOOD::setModificationDate> gmtime failed (mModificationDateTime = " << mModificationDateTime << ")" << std::endl;
        return false;
    }
    lModificationDateTimeStruct->tm_mday = lDateTimeStruct.tm_mday;
    lModificationDateTimeStruct->tm_mon = lDateTimeStruct.tm_mon;
    lModificationDateTimeStruct->tm_year = lDateTimeStruct.tm_year;
    mModificationDateTime = mktime(lModificationDateTimeStruct);

    return true;
}

bool OSCOOD::setModificationTime(const std::string &pTime) {
    struct tm lDateTimeStruct;
    std::memset(&lDateTimeStruct, 0, sizeof(struct tm));

    /* The input string should only contain the time
     * in either the AM/PM format
     * or the 24-hour format
     */

    if(strptime(pTime.c_str(), "%I:%M%p", &lDateTimeStruct)) {
        /* Do nothing */
    } else if (strptime(pTime.c_str(), "%H:%M:%S", &lDateTimeStruct)) {
        /* Do nothing */
    } else if (strptime(pTime.c_str(), "%H:%M", &lDateTimeStruct)) {
        /* Do nothing */
    } else {
        std::cerr << "[ERROR] <OSCOOD::setModificationTime> Wrong time format" << std::endl;
        return false;
    }

    struct tm *lModificationDateTimeStruct = gmtime(&mModificationDateTime);
    if(nullptr == lModificationDateTimeStruct) {
        std::cerr << "[ERROR] <OSCOOD::setModificationTime> gmtime failed (mModificationDateTime = " << mModificationDateTime << ")" << std::endl;
        return false;
    }
    lModificationDateTimeStruct->tm_hour = lDateTimeStruct.tm_hour;
    lModificationDateTimeStruct->tm_min  = lDateTimeStruct.tm_min;
    lModificationDateTimeStruct->tm_sec  = lDateTimeStruct.tm_sec;
    mModificationDateTime = mktime(lModificationDateTimeStruct);

    return true;
}

void OSCOOD::setModificationDateTime(const std::time_t &pDateTime) {
    mModificationDateTime = pDateTime;
}

void OSCOOD::setModifiedBy(const std::string &pModifiedBy) {
    mModifiedBy = pModifiedBy;
}

void OSCOOD::setVendorName(const std::string &pName) {
    mVendorName = pName;
}

void OSCOOD::setVendorNumber(const uint32_t &pNumber) {
    mVendorNumber = pNumber;
}

void OSCOOD::setProductName(const std::string &pName) {
    mProductName = pName;
}

void OSCOOD::setProductNumber(const uint32_t &pNumber) {
    mProductNumber = pNumber;
}

void OSCOOD::setRevisionNumber(const uint32_t &pRevision) {
    mRevisionNumber = pRevision;
}

void OSCOOD::setOrderCode(const std::string &pOrderCode) {
    mOrderCode = pOrderCode;
}

void OSCOOD::setBaudrate10Supported(const bool &pSupport) {
    mBaudRate_10 = pSupport;
}

void OSCOOD::setBaudrate20Supported(const bool &pSupport) {
    mBaudRate_20 = pSupport;
}

void OSCOOD::setBaudrate50Supported(const bool &pSupport) {
    mBaudRate_50 = pSupport;
}

void OSCOOD::setBaudrate125Supported(const bool &pSupport) {
    mBaudRate_125 = pSupport;
}

void OSCOOD::setBaudrate250Supported(const bool &pSupport) {
    mBaudRate_250 = pSupport;
}

void OSCOOD::setBaudrate500Supported(const bool &pSupport) {
    mBaudRate_500 = pSupport;
}

void OSCOOD::setBaudrate800Supported(const bool &pSupport) {
    mBaudRate_800 = pSupport;
}

void OSCOOD::setBaudrate1000Supported(const bool &pSupport) {
    mBaudRate_1000 = pSupport;
}

void OSCOOD::setSimpleBootUpMaster(const bool &pSupport) {
    mBaudRate_10 = pSupport;
}

void OSCOOD::setSimpleBootUpSlave(const bool &pSupport) {
    mBaudRate_10 = pSupport;
}

void OSCOOD::setGranularity(const uint8_t &pGranularity) {
    mGranularity = pGranularity;
}

void OSCOOD::setDynamicChannelsSupported(const uint8_t &pChannelCount) {
    mDynamicChannelsSupported = pChannelCount;
}

void OSCOOD::setGroupMessaging(const bool &pSupport) {
    mGroupMessaging = pSupport;
}

void OSCOOD::setNrOfRPDOs(const uint16_t &pRPDONb) {
    mNrOfRXPDO = pRPDONb;
}

void OSCOOD::setNrOfTPDOs(const uint16_t &pTPDONb) {
    mNrOfTXPDO = pTPDONb;
}

void OSCOOD::setLSSSupported(const bool &pSupport) {
    mLSSSupported = pSupport;
}

void OSCOOD::setComments(const std::string &pComments) {
    mComments = pComments;

    std::istringstream lISS(mComments);
    uint32_t lLineCount = 0U;
    for(std::string lLine; std::getline(lISS, lLine);) {
        ++lLineCount;
    }
}

void OSCOOD::setDummy0001Supported(const bool &pSupport) {
    mDummy0001 = pSupport;
}

void OSCOOD::setDummy0002Supported(const bool &pSupport) {
    mDummy0002 = pSupport;
}

void OSCOOD::setDummy0003Supported(const bool &pSupport) {
    mDummy0003 = pSupport;
}

void OSCOOD::setDummy0004Supported(const bool &pSupport) {
    mDummy0004 = pSupport;
}

void OSCOOD::setDummy0005Supported(const bool &pSupport) {
    mDummy0005 = pSupport;
}

void OSCOOD::setDummy0006Supported(const bool &pSupport) {
    mDummy0006 = pSupport;
}

void OSCOOD::setDummy0007Supported(const bool &pSupport) {
    mDummy0007 = pSupport;
}

bool OSCOOD::setDummySupported(const uint8_t &pDummy, const bool &pSupport) {
    if(1U > pDummy || 7 < pDummy) {
        std::cerr << "[ERROR] <OSCOOD::setDummy0007Supported> pDummy out of bounds" << std::endl;
        return false;
    }

    switch(pDummy) {
        case 1U:
            setDummy0001Supported(pSupport);
            break;
        case 2U:
            setDummy0002Supported(pSupport);
            break;
        case 3U:
            setDummy0003Supported(pSupport);
            break;
        case 4U:
            setDummy0004Supported(pSupport);
            break;
        case 5U:
            setDummy0005Supported(pSupport);
            break;
        case 6U:
            setDummy0006Supported(pSupport);
            break;
        case 7U:
            setDummy0007Supported(pSupport);
            break;
        default:
            std::cerr << "[ERROR] <OSCOOD::setDummySupported> pDummy out of bounds" << std::endl;
            return false;
    }

    return true;
}

void OSCOOD::setCustomHeader(const std::string &pHeaderName) {
    mCustomHeader = pHeaderName;
}

void OSCOOD::setSourceFilePath(const std::string &pSourceFilePath) {
    mSourceFilePath = pSourceFilePath;
}
