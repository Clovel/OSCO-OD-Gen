/**
 * @brief OSCOOD class
 * 
 * @file OSCOOD.hpp
 */

#ifndef OSCOOD_HPP
#define OSCOOD_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* C++ system */
#include <map>
#include <vector>
#include <exception>
#include <string>

/* C System */
#include <cstdint>
#include <ctime>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOODIndex;

/* OSCOOD exception ------------------------------------ */
class OSCOODException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "OSCOOD exception occured !";
    }
};

/* OSCOOD class ---------------------------------- */
class API_EXPORT OSCOOD {
    public:
        /* Constructors */
        OSCOOD();
        OSCOOD(const std::map<uint16_t, OSCOODIndex *> &pObjects);
        OSCOOD(const std::vector<OSCOODIndex *> &pObjects);

        /**
         * @brief This copy constructor can take the ownership of the
         * OSCOODIndex opbjects contained within the source OSCOOD instance.
         * 
         * @details Using the pTakeOwnership parameter, you can take
         * or not the ownership of the OSCOODIndex contained in the source
         * OSCOOD instance.
         * 
         * @param[in]   pOD             Source OSCOOD instance to copy.
         * @param[in]   pTakeOwnership  Weither to take ownership or not.
         *  `true` by default
         */
        OSCOOD(OSCOOD &pOD, const bool &pTakeOwnership = true);

        /* Destructor */
        virtual ~OSCOOD();

        /* Getters */
        std::map<uint16_t, OSCOODIndex *> indexes(void) const;

        std::string name(void) const;

        std::string fileName(void) const;
        uint8_t     fileVersion(void) const;
        uint8_t     fileRevision(void) const;
        std::string EDSVersion(void) const;
        std::string description(void) const;
        std::string creationDate(const bool &pFormat = false) const;
        std::string creationTime(const bool &pFormat = false) const;
        std::time_t creationDateTime(void) const;
        std::string createdBy(void) const;
        std::string modificationDate(const bool &pFormat = false) const;
        std::string modificationTime(const bool &pFormat = false) const;
        std::time_t modificationDateTime(void) const;
        std::string modifiedBy(void) const;

        std::string vendorName(void) const;
        uint32_t    vendorNumber(void) const;
        std::string productName(void) const;
        uint32_t    productNumber(void) const;
        uint32_t    revisionNumber(void) const;
        std::string orderCode(void) const;
        bool        baudrate10Supported(void) const;
        bool        baudrate20Supported(void) const;
        bool        baudrate50Supported(void) const;
        bool        baudrate125Supported(void) const;
        bool        baudrate250Supported(void) const;
        bool        baudrate500Supported(void) const;
        bool        baudrate800Supported(void) const;
        bool        baudrate1000Supported(void) const;
        bool        simpleBootUpMaster(void) const;
        bool        simpleBootUpSlave(void) const;
        uint8_t     granularity(void) const;
        uint8_t     dynamicChannelsSupported(void) const;
        bool        groupMessaging(void) const;
        uint16_t    nrOfRPDOs(void) const;
        uint16_t    nrOfTPDOs(void) const;
        bool        LSSSupported(void) const;

        std::string comments(void) const;
        std::string commentLine(const uint32_t &pLine) const;
        uint32_t    commentLineCount(void) const;

        bool dummy0001Supported(void) const;
        bool dummy0002Supported(void) const;
        bool dummy0003Supported(void) const;
        bool dummy0004Supported(void) const;
        bool dummy0005Supported(void) const;
        bool dummy0006Supported(void) const;
        bool dummy0007Supported(void) const;
        bool dummySupported(const uint8_t &pDummy, bool &pSupported) const;

        std::string customHeader(void) const;
        std::string sourceFilePath(void) const;

        bool ownership(void) const;

        /* Setters */
        bool addIndex(OSCOODIndex *pIndex);
        bool removeIndex(const OSCOODIndex * const pIndex);
        bool removeIndex(const uint16_t &pIndex);

        void setName(const std::string &pName);

        void setFileName(const std::string &pFileName);
        void setFileVersion(const uint8_t &pVersion);
        void setFileRevision(const uint8_t &pRevision);
        void setEDSVersion(const std::string &pVersion);
        void setDescription(const std::string &pDescription);
        bool setCreationDate(const std::string &pDate);
        bool setCreationTime(const std::string &pTime);
        void setCreationDateTime(const std::time_t &pDateTime);
        void setCreatedBy(const std::string &pCreatedBy);
        bool setModificationDate(const std::string &pDate);
        bool setModificationTime(const std::string &pTime);
        void setModificationDateTime(const std::time_t &pDateTime);
        void setModifiedBy(const std::string &pModifiedBy);

        void setVendorName(const std::string &pName);
        void setVendorNumber(const uint32_t &pNumber);
        void setProductName(const std::string &pName);
        void setProductNumber(const uint32_t &pNumber);
        void setRevisionNumber(const uint32_t &pRevision);
        void setOrderCode(const std::string &pOrderCode);
        void setBaudrate10Supported(const bool &pSupport);
        void setBaudrate20Supported(const bool &pSupport);
        void setBaudrate50Supported(const bool &pSupport);
        void setBaudrate125Supported(const bool &pSupport);
        void setBaudrate250Supported(const bool &pSupport);
        void setBaudrate500Supported(const bool &pSupport);
        void setBaudrate800Supported(const bool &pSupport);
        void setBaudrate1000Supported(const bool &pSupport);
        void setSimpleBootUpMaster(const bool &pSupport);
        void setSimpleBootUpSlave(const bool &pSupport);
        void setGranularity(const uint8_t &pGranularity);
        void setDynamicChannelsSupported(const uint8_t &pChannelCount);
        void setGroupMessaging(const bool &pSupport);
        void setNrOfRPDOs(const uint16_t &pRPDONb);
        void setNrOfTPDOs(const uint16_t &pTPDONb);
        void setLSSSupported(const bool &pSupport);

        void setComments(const std::string &pComments);

        void setDummy0001Supported(const bool &pSupport);
        void setDummy0002Supported(const bool &pSupport);
        void setDummy0003Supported(const bool &pSupport);
        void setDummy0004Supported(const bool &pSupport);
        void setDummy0005Supported(const bool &pSupport);
        void setDummy0006Supported(const bool &pSupport);
        void setDummy0007Supported(const bool &pSupport);
        bool setDummySupported(const uint8_t &pDummy, const bool &pSupport);

        void setCustomHeader(const std::string &pHeaderName);
        void setSourceFilePath(const std::string &pSourceFilePath);

        void setOwnership(const bool &pOwner);
    protected:
    private:
        std::map<uint16_t, OSCOODIndex *> mObjects; /**< Contents of the Object Dictionary */

        std::string mName; /**< Name of the Object Dictionary */

        /* FileInfo -------------------------- */

        std::string mFileName; /**< Shall indicate the file name (according to OS restrictions) */
        uint8_t mFileVersion; /**< Shall indicate the actual file version (Unsigned8) */
        uint8_t mFileRevision; /**< Shall indicate the actual file revision (Unsigned8) */
        
        /**
         * @brief Shall indicate the version of the specification (3 characters) in the format “x.y”.
         * If the entry is missing, this is equal to “3.0”.
         * 
         * @warning EDS files should use at least “4.0", as it's the specification version
         * used for the development of this project.
         */
        std::string mEDSVersion;

        std::string mDescription; /**< Shall provide a file description (max 243 characters) */

        /** 
         * @brief Shall provide the file creation time (24-hour "hh:mm:ss" format)
         * and date (DD/MM/YYYY format)
         * 
         * @warning The specification actually specifies the "hh:mm (AP|PM)" 12-hour format,
         * but it is less used than the european 24-hour format.
         * 
         * @details This will hold both the CreationTime and CreationDate attributes.
         */
        std::time_t mCreationDateTime;

        std::string mCreatedBy; /**< shall provide the name or a description of the file creator (max. 245 characters) */

        /** 
         * @brief Shall provide the file modification time (24-hour "hh:mm:ss" format)
         * and date (DD/MM/YYYY format)
         * 
         * @warning The specification actually specifies the "hh:mm (AP|PM)" 12-hour format,
         * but it is less used than the european 24-hour format.
         * 
         * @details This will hold both the ModificationTime and ModificationDate attributes.
         */
        std::time_t mModificationDateTime;

        std::string mModifiedBy; /**< shall provide the name or a description of the file updator (max. 245 characters) */

        /* DeviceInfo ------------------------ */
        std::string mVendorName; /**< shall provide the vendor name (max. 244 characters) */
        uint32_t mVendorNumber; /**< shall provide the unique vendor ID according to identity object sub-index 01h (Unsigned32) */

        std::string mProductName; /**< shall provide the product name (max. 243 characters) */
        uint32_t mProductNumber; /**< shall provide the product code according to identity object sub-index 02h (Unsigned32) */

        uint32_t mRevisionNumber; /**< shall provide the product revision number according to identity object sub-index 03h (Unsigned32) */

        std::string mOrderCode; /**< shall provide the order code for this product (max. 245 characters) */
        
        bool mBaudRate_10; /**< Shall indicate if the 10kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_20; /**< Shall indicate if the 20kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_50; /**< Shall indicate if the 50kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_125; /**< Shall indicate if the 125kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_250; /**< Shall indicate if the 250kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_500; /**< Shall indicate if the 500kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_800; /**< Shall indicate if the 800kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */
        bool mBaudRate_1000; /**< Shall indicate if the 1000kbps baudrate is supported (Boolean, 0 = not supported, 1=supported) */

        bool mSimpleBootUpMaster; /**< Shall indicate the simple boot-up master functionality */
        bool mSimpleBootUpSlave; /**< Shall indicate the simple boot-up slave functionality */

        /**
         * @breif Shall provide the granularity allowed for the mapping on this device.
         * 
         * @details Most of the existing devices support a granularity of 8 
         * - 0 - mapping not modifiable
         * - [1; 64] mapping granularity
         * 
         * TODO : ???
         * Default is 8 for now
         */
        uint8_t mGranularity;

        /**
         * @breif Indicates the facility of dynamic variable generation.
         * If the value is unequal to 0, the additional section DynamicChannels exists.
         * 
         * TODO : ???
         * Default is 0 for now
         */
        uint8_t mDynamicChannelsSupported;

        bool mGroupMessaging; /**< 1 : MPDOs are supported, 0 : MPDOs are not supported */

        uint16_t mNrOfRXPDO; /**< Number of supported RPDOs */
        uint16_t mNrOfTXPDO; /**< Number of supported TPDOs */

        bool mLSSSupported; /**< Indicate if the LSS feature is supported */

        /* Comments -------------------------- */
        std::string mComments; /**< EDS Comments */
        uint32_t    mCommentLineCount; /**< Number of comment lines */

        /* DummyUsage ------------------------ */
        /* TODO : Which mapping dummy for which basic type ? */
        bool mDummy0001; /**< Indicated if the usage of Dummy0001 is supported */
        bool mDummy0002; /**< Indicated if the usage of Dummy0002 is supported */
        bool mDummy0003; /**< Indicated if the usage of Dummy0003 is supported */
        bool mDummy0004; /**< Indicated if the usage of Dummy0004 is supported */
        bool mDummy0005; /**< Indicated if the usage of Dummy0005 is supported */
        bool mDummy0006; /**< Indicated if the usage of Dummy0006 is supported */
        bool mDummy0007; /**< Indicated if the usage of Dummy0007 is supported */

        /* Data not set in the source file */
        std::string mCustomHeader; /**< Header defined by the user. Added in generated OD header */
        std::string mSourceFilePath; /**< Absolute path to the source file used to create/save this OD instance */

        /** @brief This properies dictates the ownership of the indexes and subindexes
         * contained by this class instance.
         * 
         * @details If the ownership is to be shifted, then upon deletion of this instance the
         * OSCOIndexes will not be deleted. Default is true.
         * 
         * @warning If used incorrectly, this can lead to memory leakage.
         */
        bool mOwnership;
};

#endif /* OSCOOD_HPP */