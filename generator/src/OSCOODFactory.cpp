/**
 * @brief OSCOODFactory class implementation
 * 
 * @file OSCOODFactory.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODFactory.hpp"
#include "OSCOODIndex.hpp"
#include "OSCOODSubIndex.hpp"
#include "OSCOOD.hpp"

/* EDS */
#include "EDS.hpp"
#include "EDSTools.hpp"

/* C++ System */
#include <string>
#include <iostream>
#include <sstream>

/* Defines --------------------------------------------- */
#define NB_GENERIC_KEYS 11U /**< Number of accepted keys for OSCOODObjects */

/* Type definitions ------------------------------------ */
typedef enum _fileType {
    FILE_UNKNOWN = 0U,
    FILE_EDS,
    FILE_DCF,
    FILE_XML,
    FILE_JSON
} configFileType_t;

/* Helper functions ------------------------------------ */
static bool compareChar(const char &pChar1, const char &pChar2)
{
    if (pChar1 == pChar2)
        return true;
    else if (std::toupper(pChar1) == std::toupper(pChar2))
        return true;
    return false;
}

static bool caseInSensStringCompare(const std::string &pStr1, const std::string &pStr2)
{
    return ((pStr1.size() == pStr2.size()) &&
        std::equal(pStr1.begin(), pStr1.end(), pStr2.begin(), &compareChar) );
}

static configFileType_t indentifyFileType(const std::string &pFile) {
    static const std::string sEDSExt = ".eds";
    static const std::string sDCFExt = ".dcf";
    static const std::string sXMLExt = ".xml";

    std::string lExt = pFile.substr(pFile.find_last_of('.'));

    if(caseInSensStringCompare(sEDSExt, lExt)) {
        return FILE_EDS;
    }

    if(caseInSensStringCompare(sDCFExt, lExt)) {
        return FILE_DCF;
    }

    if(caseInSensStringCompare(sXMLExt, lExt)) {
        return FILE_XML;
    }

    return FILE_UNKNOWN;
}

/**
 * @brief Fills in the given OSCOODObject's attributes with
 * a Key/Value pair from the EDS file.
 * 
 * @param[in]   pObj    OSCO OD Object to fill
 * @param[in]   pKey    Key of the EDS data
 * @param[in]   pVal    Value associated with the given key
 * 
 * @return true if success, false elsewise.
 */
static bool fillObjectAtrributes(OSCOODObject * const pObj, const std::string pKey, const std::string pVal) {
    if(nullptr == pObj) {
        std::cerr << "[ERROR] <fillObjectAtrributes> Input argument is nullptr" << std::endl;
        return false;
    }

    /* Accepted generic keys */
    static const std::string sGenericKeys[NB_GENERIC_KEYS] = {
        "SubNumber",
        "ParameterName",
        "ObjectType",
        "DataType",
        "AccessType",
        "DefaultValue"
        "LowLimit",
        "HighLimit",
        "PDOMapping",
        "ObjFlags",
        "CompactSubObj"
    };
    /* Accepted OSCOODIndex specific keys */
    /* Accepted OSCOODSubIndex specific keys */
    
    /* First, go through generic attributes */

    /* SubNumber */
    if(caseInSensStringCompare(sGenericKeys[0U], pKey)) {
        unsigned int lTempVal = 0U;
        if("0x" == pVal.substr(0U, 2U)) {
            std::sscanf(pVal.c_str(), "%x", &lTempVal);
        } else {
            std::sscanf(pVal.c_str(), "%u", &lTempVal);
        }

        if(0U <= lTempVal && 0xFFU >= lTempVal)
            pObj->setSubNumber((uint8_t)lTempVal);
        else {
            std::cerr << "[ERROR] <fillObjectAtrributes> SubNumber is out of bounds (" << lTempVal << ")" << std::endl;
            return false;
        }
    }

    /* ParameterName */
    if(caseInSensStringCompare(sGenericKeys[1U], pKey)) {
        pObj->setParamName(pVal);
    }

    /* ObjectType */
    if(caseInSensStringCompare(sGenericKeys[2U], pKey)) {
        unsigned int lTempVal = 0U;
        if("0x" == pVal.substr(0U, 2U)) {
            std::sscanf(pVal.c_str(), "%x", &lTempVal);
        } else {
            std::sscanf(pVal.c_str(), "%u", &lTempVal);
        }

        if(0U <= lTempVal && 0xFFU >= lTempVal)
            pObj->setObjectType((uint8_t)lTempVal);
        else {
            std::cerr << "[ERROR] <fillObjectAtrributes> ObjectType is out of bounds (" << lTempVal << ")" << std::endl;
            return false;
        }
    }

    /* DataType */
    if(caseInSensStringCompare(sGenericKeys[3U], pKey)) {
        unsigned int lTempVal = 0U;
        if("0x" == pVal.substr(0U, 2U)) {
            std::sscanf(pVal.c_str(), "%x", &lTempVal);
        } else {
            std::sscanf(pVal.c_str(), "%u", &lTempVal);
        }

        if(0U <= lTempVal && 0xFFU >= lTempVal)
            pObj->setDataType((uint8_t)lTempVal);
        else {
            std::cerr << "[ERROR] <fillObjectAtrributes> DataType is out of bounds (" << lTempVal << ")" << std::endl;
            return false;
        }
    }

    /* AccessType */
    if(caseInSensStringCompare(sGenericKeys[4U], pKey)) {
        pObj->setAccessType(pVal);
    }

    /* DefaultValue */
    if(caseInSensStringCompare(sGenericKeys[5U], pKey)) {
        pObj->setDefaultValue(pVal);
    }

    /* LowLimit */
    if(caseInSensStringCompare(sGenericKeys[6U], pKey)) {
        pObj->setLowLimit(pVal);
    }

    /* HighLimit */
    if(caseInSensStringCompare(sGenericKeys[7U], pKey)) {
        pObj->setHighLimit(pVal);
    }

    /* PDOMapping */
    if(caseInSensStringCompare(sGenericKeys[8U], pKey)) {
        if((pVal == "true")
            || (pVal == "True")
            || (pVal == "1"))
        {
            pObj->allowPDOMapping();
        } else if ((pVal == "false")
            || (pVal == "False")
            || (pVal == "0"))
        {
            pObj->forbidPDOMapping();
        } else {
            std::cerr << "[ERROR] <fillObjectAtrributes> PDOMapping value unknown (" << pVal << ")" << std::endl;
            return false;
        }
    }

    /* ObjFlags */
    if(caseInSensStringCompare(sGenericKeys[9U], pKey)) {
        unsigned int lTempVal = 0U;
        if("0x" == pVal.substr(0U, 2U)) {
            std::sscanf(pVal.c_str(), "%x", &lTempVal);
        } else {
            std::sscanf(pVal.c_str(), "%u", &lTempVal);
        }

        pObj->setObjFlags((uint32_t)lTempVal);
    }

    /* CompactSubObj */
    if(caseInSensStringCompare(sGenericKeys[9U], pKey)) {
        unsigned int lTempVal = 0U;
        if("0x" == pVal.substr(0U, 2U)) {
            std::sscanf(pVal.c_str(), "%x", &lTempVal);
        } else {
            std::sscanf(pVal.c_str(), "%u", &lTempVal);
        }

        if(0U <= lTempVal && 0xFFU >= lTempVal)
            pObj->setCompactSubObj((uint8_t)lTempVal);
        else {
            std::cerr << "[ERROR] <fillObjectAtrributes> CompactSubObj is out of bounds (" << lTempVal << ")" << std::endl;
            return false;
        }
    }

    /* Go through OSCOODIndex specific attributes */
    
    /* Go through OSCOODSubIndex specific attributes */

    return true;
}

static bool fillOSCOODFileInfo(const INI * const pINI, OSCOOD * const pOD) {
    /* Check arguments */
    if(nullptr == pINI) {
        std::cerr << "[ERROR] <fillOSCOODFileInfo> INI file arg is nullptr" << std::endl;
        return false;
    }

    if(nullptr == pOD) {
        std::cerr << "[ERROR] <fillOSCOODFileInfo> OSCO OD arg is nullptr" << std::endl;
        return false;
    }

    /* check that the INI file has a FileInfo section */
    if(!pINI->sectionExists("FileInfo")) {
        std::cerr << "[ERROR] <fillOSCOODFileInfo> INI file has no FileInfo section" << std::endl;
        return false;
    }

    /* Get the FileInfo */
    std::string lTempVal = "";
    if(0 == pINI->getValue("FileName", lTempVal, "FileInfo")) {
        pOD->setFileName(lTempVal);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : FileName" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("FileVersion", lTempVal, "FileInfo")) {
        /* Convert string to uint */
        unsigned long lFileVersion = 0U;
        try {
            lFileVersion = stoul(lTempVal);
            if(0xFFU < lFileVersion) {
                std::cerr << "[ERROR] <fillOSCOODFileInfo> FileVersion is out of bounds" << std::endl;
                return false;
            }
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> FileVersion value invalid" << std::endl;
            return false;
        }

        pOD->setFileVersion((uint8_t)lFileVersion);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : FileVersion" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("FileRevision", lTempVal, "FileInfo")) {
        /* Convert string to uint */
        unsigned long lFileRevision = 0U;
        try {
            lFileRevision = stoul(lTempVal);
            if(0xFFU < lFileRevision) {
                std::cerr << "[ERROR] <fillOSCOODFileInfo> FileRevision is out of bounds" << std::endl;
                return false;
            }
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> FileRevision value invalid" << std::endl;
            return false;
        }

        pOD->setFileRevision((uint8_t)lFileRevision);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : FileRevision" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("EDSVersion", lTempVal, "FileInfo")) {
        pOD->setEDSVersion(lTempVal);
    } else {
        /* Optional : If this entry is missing, value is "3.0" */
        pOD->setEDSVersion("3.0");
    }

    if(0 == pINI->getValue("Description", lTempVal, "FileInfo")) {
        if(243U < lTempVal.size()) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> Description string is too long" << std::endl;
            return false;
        }
        pOD->setDescription(lTempVal);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : Description" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("CreationTime", lTempVal, "FileInfo")) {
        if(!pOD->setCreationTime(lTempVal)) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> setCreationTime failed" << std::endl;
            return false;
        }
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : CreationTime" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("CreationDate", lTempVal, "FileInfo")) {
        if(!pOD->setCreationDate(lTempVal)) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> setCreationDate failed" << std::endl;
            return false;
        }
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : CreationDate" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("CreatedBy", lTempVal, "FileInfo")) {
        pOD->setCreatedBy(lTempVal);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODFileInfo> Missing mandatory FileInfo key : CreatedBy" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("ModificationTime", lTempVal, "FileInfo")) {
        if(!pOD->setModificationTime(lTempVal)) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> setModificationTime failed" << std::endl;
            return false;
        }
    } else {
        /* Optional */
        std::cerr << "[WARN ] <fillOSCOODFileInfo> Missing optional FileInfo key : ModificationTime" << std::endl;
    }

    if(0 == pINI->getValue("ModificationDate", lTempVal, "FileInfo")) {
        if(!pOD->setModificationDate(lTempVal)) {
            std::cerr << "[ERROR] <fillOSCOODFileInfo> setModificationDate failed" << std::endl;
            return false;
        }
    } else {
        /* Optional */
        std::cerr << "[WARN ] <fillOSCOODFileInfo> Missing optional FileInfo key : ModificationDate" << std::endl;
    }

    if(0 == pINI->getValue("ModifiedBy", lTempVal, "FileInfo")) {
        pOD->setModifiedBy(lTempVal);
    } else {
        /* Optional */
        std::cerr << "[WARN ] <fillOSCOODFileInfo> Missing optional FileInfo key : ModifiedBy" << std::endl;
    }

    return true;
}

static bool fillOSCOODDeviceInfo(const INI * const pINI, OSCOOD * const pOD) {
    /* Check arguments */
    if(nullptr == pINI) {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file arg is nullptr" << std::endl;
        return false;
    }

    if(nullptr == pOD) {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> OSCO OD arg is nullptr" << std::endl;
        return false;
    }

    /* check that the INI file has a FileInfo section */
    if(!pINI->sectionExists("DeviceInfo")) {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no DeviceInfo section" << std::endl;
        return false;
    }

    /* Get the DeviceInfo */
    std::string lTempVal = "";
    if(0 == pINI->getValue("VendorName", lTempVal, "DeviceInfo")) {
        pOD->setVendorName(lTempVal);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : VendorName" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("VendorNumber", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lVendorNumber = 0U;

        try {
            lVendorNumber = stoul(lTempVal);
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> VendorNumber value invalid" << std::endl;
            return false;
        }

        pOD->setVendorNumber((uint8_t)lVendorNumber);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : VendorNumber" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("ProductName", lTempVal, "DeviceInfo")) {
        pOD->setProductName(lTempVal);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : ProductName" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("ProductNumber", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lProductNumber = 0U;

        try {
            lProductNumber = stoul(lTempVal);
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> ProductNumber value invalid" << std::endl;
            return false;
        }

        pOD->setProductNumber((uint8_t)lProductNumber);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : ProductNumber" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("RevisionNumber", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lRevisionNumber = 0U;

        try {
            lRevisionNumber = stoul(lTempVal);
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> RevisionNumber value invalid" << std::endl;
            return false;
        }

        pOD->setRevisionNumber((uint8_t)lRevisionNumber);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : RevisionNumber" << std::endl;
        return false;
    }


    if(0 == pINI->getValue("OrderCode", lTempVal, "DeviceInfo")) {
        pOD->setOrderCode(lTempVal);
    } else {
        /* Optional */
        std::cerr << "[WARN ] <fillOSCOODDeviceInfo> Missing optional DeviceInfo key : OrderCode" << std::endl;
        pOD->setOrderCode("");
    }

    if(0 == pINI->getValue("BaudRate_10", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate10Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate10Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_10 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_10 key" << std::endl;
        pOD->setBaudrate10Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_20", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate20Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate20Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_20 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_20 key" << std::endl;
        pOD->setBaudrate20Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_50", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate50Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate50Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_50 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_50 key" << std::endl;
        pOD->setBaudrate50Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_125", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate125Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate125Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_125 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_125 key" << std::endl;
        pOD->setBaudrate125Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_250", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate250Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate250Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_250 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_250 key" << std::endl;
        pOD->setBaudrate250Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_500", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate500Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate500Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_500 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_500 key" << std::endl;
        pOD->setBaudrate500Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_800", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate800Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate800Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_800 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_800 key" << std::endl;
        pOD->setBaudrate800Supported(false);
    }

    if(0 == pINI->getValue("BaudRate_1000", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setBaudrate1000Supported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setBaudrate1000Supported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid BaudRate_1000 value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no BaudRate_1000 key" << std::endl;
        pOD->setBaudrate1000Supported(false);
    }

    if(0 == pINI->getValue("SimpleBootUpMaster", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setSimpleBootUpMaster(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setSimpleBootUpMaster(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid SimpleBootUpMaster value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no SimpleBootUpMaster key" << std::endl;
        pOD->setSimpleBootUpMaster(false);
    }

    if(0 == pINI->getValue("SimpleBootUpSlave", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setSimpleBootUpSlave(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setSimpleBootUpSlave(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid SimpleBootUpSlave value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no SimpleBootUpSlave key" << std::endl;
        pOD->setSimpleBootUpSlave(false);
    }

    if(0 == pINI->getValue("Granularity", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lGranularity = 0U;
        try {
            lGranularity = stoul(lTempVal);
            if(0xFFU < lGranularity) {
                std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Granularity is out of bounds" << std::endl;
                return false;
            }
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Granularity value invalid" << std::endl;
            return false;
        }

        pOD->setGranularity((uint8_t)lGranularity);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : Granularity" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("DynamicChannelsSupported", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setDynamicChannelsSupported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setDynamicChannelsSupported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid DynamicChannelsSupported value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no DynamicChannelsSupported key" << std::endl;
        pOD->setDynamicChannelsSupported(false);
    }

    if(0 == pINI->getValue("GroupMessaging", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setGroupMessaging(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setGroupMessaging(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid GroupMessaging value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no GroupMessaging key" << std::endl;
        pOD->setGroupMessaging(false);
    }

    if(0 == pINI->getValue("NrOfRXPDO", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lNrOfRXPDO = 0U;
        try {
            lNrOfRXPDO = stoul(lTempVal);
            if(0xFFFFU < lNrOfRXPDO) {
                std::cerr << "[ERROR] <fillOSCOODDeviceInfo> NrOfRXPDO is out of bounds" << std::endl;
                return false;
            }
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> NrOfRXPDO value invalid" << std::endl;
            return false;
        }

        pOD->setNrOfRPDOs((uint16_t)lNrOfRXPDO);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : NrOfRXPDO" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("NrOfTXPDO", lTempVal, "DeviceInfo")) {
        /* Convert string to uint */
        unsigned long lNrOfTXPDO = 0U;
        try {
            lNrOfTXPDO = stoul(lTempVal);
            if(0xFFFFU < lNrOfTXPDO) {
                std::cerr << "[ERROR] <fillOSCOODDeviceInfo> NrOfTXPDO is out of bounds" << std::endl;
                return false;
            }
        } catch (std::exception &e) {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> NrOfTXPDO value invalid" << std::endl;
            return false;
        }

        pOD->setNrOfTPDOs((uint16_t)lNrOfTXPDO);
    } else {
        /* Mandatory */
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Missing mandatory DeviceInfo key : NrOfTXPDO" << std::endl;
        return false;
    }

    if(0 == pINI->getValue("LSS_Supported", lTempVal, "DeviceInfo")) {
        if((lTempVal == "true")
            || (lTempVal == "True")
            || (lTempVal == "1"))
        {
            pOD->setLSSSupported(true);
        } else if ((lTempVal == "false")
            || (lTempVal == "False")
            || (lTempVal == "0"))
        {
            pOD->setLSSSupported(false);
        } else {
            std::cerr << "[ERROR] <fillOSCOODDeviceInfo> Invalid LSS_Supported value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "[ERROR] <fillOSCOODDeviceInfo> INI file has no LSS_Supported key" << std::endl;
        pOD->setLSSSupported(false);
    }

    return true;
}

static bool fillOSCOODDummyUsage(const INI * const pINI, OSCOOD * const pOD) {
    /* Check arguments */
    if(nullptr == pINI) {
        std::cerr << "[ERROR] <fillOSCOODDummyUsage> INI file arg is nullptr" << std::endl;
        return false;
    }

    if(nullptr == pOD) {
        std::cerr << "[ERROR] <fillOSCOODDummyUsage> OSCO OD arg is nullptr" << std::endl;
        return false;
    }

    pOD->setDummy0001Supported(false);
    pOD->setDummy0002Supported(false);
    pOD->setDummy0003Supported(false);
    pOD->setDummy0004Supported(false);
    pOD->setDummy0005Supported(false);
    pOD->setDummy0006Supported(false);
    pOD->setDummy0007Supported(false);

    /* check that the INI file has a FileInfo section */
    if(!pINI->sectionExists("FileInfo")) {
        std::cerr << "[ERROR] <fillOSCOODDummyUsage> INI file has no DummyUsage section" << std::endl;
        return true;
    }

    static const std::string lDummyKeyBase = "Dummy000";
    std::string lTempVal      = "";
    for(uint8_t i = 1U; i < 8U; i++) {
        std::string lDummyKey = lDummyKeyBase + (char)(i + 48U); /* ASCII Offset */
        if(0 == pINI->getValue(lDummyKey, lTempVal, "DummyUsage")) {
            if((lTempVal == "true")
                || (lTempVal == "True")
                || (lTempVal == "1"))
            {
                pOD->setDummySupported(i, true);
            } else if ((lTempVal == "false")
                || (lTempVal == "False")
                || (lTempVal == "0"))
            {
                pOD->setDummySupported(i, false);
            } else {
                std::cerr << "[ERROR] <fillOSCOODDummyUsage> Invalid " << lDummyKey << " value" << std::endl;
                return false;
            }
        } else {
            std::cerr << "[ERROR] <fillOSCOODDummyUsage> INI file has no " << lDummyKey << " key" << std::endl;
            pOD->setDummySupported(i, false);
        }
    }

    return true;
}

static bool fillOSCOODComments(const INI * const pINI, OSCOOD * const pOD) {
    /* Check arguments */
    if(nullptr == pINI) {
        std::cerr << "[ERROR] <fillOSCOODComments> INI file arg is nullptr" << std::endl;
        return false;
    }
    
    if(nullptr == pOD) {
        std::cerr << "[ERROR] <fillOSCOODComments> OSCO OD arg is nullptr" << std::endl;
        return false;
    }

    /* check that the INI file has a Comments section */
    if(!pINI->sectionExists("Comments")) {
        std::cerr << "[ERROR] <fillOSCOODComments> INI file has no Comments section" << std::endl;
        return false;
    }
    
    /* Get line count */
    static const std::string lLineKeyBase = "Line";
    std::string lLineCountStr  = "";
    if(!pINI->getValue("Lines", lLineCountStr, "Comments")) {
        /* "Lines" key not found, assuming zero */
        pOD->setComments("");
    } else {
        std::string lTempVal = "", lLine = 0U;
        uint32_t lLineCount = 0U;
        std::stringstream lCommentSS;
        std::istringstream(lLineCountStr) >> lLineCount;
        for(uint32_t i = 1U; i <= lLineCount; i++) {
            std::ostringstream lOSS;
            lOSS << i;
            lLine = lOSS.str();
            if(!pINI->getValue("lLineKeyBase" + lLine, lTempVal, "Comments")) {
                std::cerr << "[ERROR] <fillOSCOODComments> Inconsistent data/linecount in Comments section" << std::endl;
            } else {
                lCommentSS << lTempVal << std::endl;
            }
        }

        /* Set the comments */
        pOD->setComments(lCommentSS.str());
    }

    return true;
}


/* OSCOODFactory class implementation ------------------ */
/* Builders */
OSCOOD *OSCOODFactory::buildOSCOOD(const std::string &pFile) {
    switch(indentifyFileType(pFile)) {
        case FILE_EDS:
            return OSCOODFromEDS(pFile);
        case FILE_DCF:
            return OSCOODFromDCF(pFile);
        case FILE_XML:
        case FILE_JSON:
        default:
            return nullptr;
            break;
    }
}

OSCONode *OSCOODFactory::buildOSCONode(const std::string &pFile) {
    switch(indentifyFileType(pFile)) {
        case FILE_EDS:
            return OSCONodeFromEDS(pFile);
        case FILE_DCF:
            return OSCONodeFromDCF(pFile);
        case FILE_XML:
        default:
            return nullptr;
            break;
    }
}

/* OSCOOD builders */
OSCOOD *OSCOODFactory::OSCOODFromEDS(const std::string &pFile) {
    /* Parse EDS file */
    EDS lEDS(pFile);

    /* Check EDS consistency */
    if(lEDS.check()) {
        std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> EDS file check failed" << std::endl;
        return nullptr;
    }

    /* Now that the EDS file is parsed & checked, we can extract it's data */

    /* Create an OSCO Object Dictionary */
    OSCOOD *lOD = new OSCOOD;

    /* Fill in the FileInfo */
    if(!fillOSCOODFileInfo(&lEDS, lOD)) {
        std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to fill in FileInfo data" << std::endl;
        delete lOD;
        return nullptr;
    }

    /* Fill in the DeviceInfo */
    if(!fillOSCOODDeviceInfo(&lEDS, lOD)) {
        std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to fill in DeviceInfo data" << std::endl;
        delete lOD;
        return nullptr;
    }

    /* Fill in the DummyUsage */
    if(!fillOSCOODDummyUsage(&lEDS, lOD)) {
        std::cerr << "[WARN ] <OSCOODFactory::OSCOODFromEDS> Failed to fill in DummyUsage data" << std::endl;
        std::cerr << "                                       Assuming NONE" << std::endl;
    }

    /* Fill in the Comments */
    if(!fillOSCOODComments(&lEDS, lOD)) {
        std::cerr << "[WARN ] <OSCOODFactory::OSCOODFromEDS> Failed to fill in Comments data" << std::endl;
        std::cerr << "                                       Assuming NONE" << std::endl;
    }

    /* Set indexes */
    const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> *lEntries = nullptr;
    lEntries = lEDS.odEntries();
    for(const auto &lEntry : *lEntries) {
        /* Temporary variables */
        std::string lTempStr = "";

        /* Check the contents of the entry key */
        if(lEntry.first.empty()) {
            continue;
        }

        uint16_t lIndex = 0U;
        if(!isIndexSection(lEntry.first, &lIndex)) {
            std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Invalid index : " << lEntry.first << std::endl;
            delete lOD;
            return nullptr;
        }

        /* Create an OSCOODIndex */
        OSCOODIndex *lOSCOODIndex = new OSCOODIndex(lIndex);

        //std::cout << "[DEBUG] <OSCOODFactory::OSCOODFromEDS> (" << lEntry.first << ") SubCount : " << lEntry.second.size() << std::endl;

        /* Set subindexes */
        for(const auto &lSubEntry : lEntry.second) {
            /* Check if this is a subindex, or just the data of the index */
            if(lEntry.first == lSubEntry.first) {
                for(const auto &lKeyVal : lSubEntry.second) {
                    if(!fillObjectAtrributes(lOSCOODIndex, lKeyVal.first, lKeyVal.second)) {
                        std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to fill Index " << lEntry.first << " attributes" << std::endl;
                        delete lOD;
                        delete lOSCOODIndex;
                        return nullptr;
                    }
                }

                continue;
            }

            /* lTempStr/lSubEntry.first should contain something like "1003sub1"
             * We must extract the subindex from this string
             */
            uint8_t lSubIndex = 0U;
            if(!isSubIdxSection(lSubEntry.first, nullptr, &lSubIndex)) {
                std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> (" << lEntry.first << ") invalid subindex : " << lSubEntry.first << std::endl;
                delete lOD;
                delete lOSCOODIndex;
                return nullptr;
            }

            /* Create an OSCOODSubIndex */
            OSCOODSubIndex *lOSCOODSubIndex = new OSCOODSubIndex(lIndex, lSubIndex);

            for(const auto &lKeyVal : lSubEntry.second) {
                if(!fillObjectAtrributes(lOSCOODSubIndex, lKeyVal.first, lKeyVal.second)) {
                    std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to fill SubIndex " << lEntry.first << ":" << lSubEntry.first << " attributes" << std::endl;
                    delete lOD;
                    delete lOSCOODIndex;
                    delete lOSCOODSubIndex;
                    return nullptr;
                }
            }

            /* Add the SubIndex to the Index */
            if(!lOSCOODIndex->addSubIndex(lOSCOODSubIndex)) {
                std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to add " << lEntry.first << ":" << lSubEntry.first << std::endl;
                delete lOD;
                delete lOSCOODIndex;
                delete lOSCOODSubIndex;
                return nullptr;
            }
        }

        /* Add the index to the object dictionary */
        if(!lOD->addIndex(lOSCOODIndex)) {
            std::cerr << "[ERROR] <OSCOODFactory::OSCOODFromEDS> Failed to add " << lEntry.first << " to Object Dictionary" << std::endl;
            delete lOD;
            delete lOSCOODIndex;
            return nullptr;
        }
    }

    return lOD;
}

OSCOOD *OSCOODFactory::OSCOODFromDCF(const std::string &pFile) {
    /* TODO : Implement the DCF factory */
    (void)pFile;

    return nullptr;
}

/* OSCONode builders */
OSCONode *OSCOODFactory::OSCONodeFromEDS(const std::string &pFile) {
    /* TODO : Implement the EDS to OSCONode factory */
    (void)pFile;

    return nullptr;
}

OSCONode *OSCOODFactory::OSCONodeFromDCF(const std::string &pFile) {
    /* TODO : Implement the DCF factory */
    (void)pFile;

    return nullptr;
}
