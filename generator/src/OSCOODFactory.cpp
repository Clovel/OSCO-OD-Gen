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

/* Defines --------------------------------------------- */
#define NB_GENERIC_KEYS 11U /**< Number of accepted keys for OSCOODObjects */

/* Type definitions ------------------------------------ */
typedef enum _fileType {
    FILE_UNKNOWN = 0U,
    FILE_EDS,
    FILE_DCF,
    FILE_XML
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

/* OSCOODFactory class implementation ------------------ */
/* Builders */
OSCOOD *OSCOODFactory::buildOSCOOD(const std::string &pFile) {
    switch(indentifyFileType(pFile)) {
        case FILE_EDS:
            return OSCOODFromEDS(pFile);
        case FILE_DCF:
            return OSCOODFromDCF(pFile);
        case FILE_XML:
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

    /* Set indexes */
    const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> * lEntries;
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
}

/* OSCONode builders */
OSCONode *OSCOODFactory::OSCONodeFromEDS(const std::string &pFile) {
    //
    (void)pFile;
}

OSCONode *OSCOODFactory::OSCONodeFromDCF(const std::string &pFile) {
    /* TODO : Implement the DCF factory */
    (void)pFile;
}
