/**
 * @brief EDS file class implementation
 * 
 * @file EDS.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"
#include "INI.hpp"

#include <string>
#include <iostream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* Static functions ------------------------------------ */
static bool isIndexSection(const std::string &pSection, uint16_t * const pIdx = nullptr) {
    uint32_t lIdx = 0U;

    /* Indexes are 4 hex characters long,
     * and do not have the "0x" prefix
     */
    if(4U != pSection.size()) {
        return false;
    }

    /* Try to convert it to a uint16_t */
    try {
        lIdx = std::stoul(pSection, nullptr, 16); /* We could use isxdigit(), but we need the value for next check */
    } catch (const std::exception &e) {
        std::cerr << "[DEBUG] <isIdxSection> std::stoul exception : " << e.what() << std::endl;
        return false;
    }

    /* Check interval */
    if(0x0000U <= lIdx && 0xFFFFU >= lIdx) {
        if(nullptr != pIdx) {
            *pIdx = (uint16_t)lIdx;
        }

        return true;
    } else {
        return false;
    }
}

static bool isSubIdxSection(const std::string &pSection, uint16_t * const pIdx = nullptr, uint8_t * const pSubIdx = nullptr) {
    const std::string lPattern = "sub";
    uint16_t          lIdx     = 0U;
    uint32_t          lSubIdx  = 0U;

    /* A sub index section contains lPattern */
    const size_t lPos = pSection.find(lPattern);
    if(std::string::npos == lPos) {
        /* lPattern was not found */
        return false;
    }

    if(4U != lPos) {
        /* There are less/more than 4 decimal before the lPattern */
        return false;
    }

    const std::string lIdxStr = pSection.substr(0U, lPos);

    if(!isIndexSection(lIdxStr, &lIdx)) {
        /* The 4 chars before the lPattern do not refer to an index */
        return false;
    }

    const std::string lSubIdxStr = pSection.substr(lPos + lPattern.size());

    try {
        lSubIdx = std::stoul(lSubIdxStr, nullptr, 16);
    } catch (const std::exception &e) {
        std::cerr << "[DEBUG] <isSubIdxSection> std::stoul exception : " << e.what() << std::endl;
        return false;
    }

    if(0U <= lSubIdx && 0xFFU >= lSubIdx) {
        if(nullptr != pSubIdx) {
            *pSubIdx = (uint8_t)lSubIdx;
        }

        if(nullptr != pIdx) {
            *pIdx = lIdx;
        }

        return true;
    } else {
        return false;
    }
}

// template<typename T>
// static std::string intToHexStr(const T &pInt, const bool &pZeroX = true) {
//     std::stringstream lStream;
//     if(pZeroX) {
//         lStream << "0x";
//     }
//     lStream << std::setfill ('0') << std::setw(sizeof(T)*2) 
//             << std::hex << pInt;
//     return lStream.str();
// }

/* EDS class implementation ---------------------------- */
/* Contructors */
EDS::EDS(const std::string &pFile) : INI(pFile) {
    /* Empty */
}

/* Destructor */
EDS::~EDS() {
    /* Empty */
}

/* EDS management */
int EDS::reorderEDSSections(void) {
    /* Empty for now */
}

/* EDS Checker */
int EDS::checkMandatoryKeys(const std::vector<std::string> &pKeys, const std::string &pSection) const {
    int lResult = 0;
    for(const auto &lElmt : pKeys) {
        if(!keyExists(lElmt, pSection)) {
            std::cerr << "[ERROR] <EDS::check> Missing key " << lElmt << " for section [" << pSection << "]" << std::endl;
            lResult = -1;
        }
    }

    return lResult;
}

int EDS::checkMandatoryValues(const std::vector<std::string> &pValues, const std::string &pSection) const {
    int lResult = 0;
    for(const auto &lExpectedElmt : pValues) {
        uint16_t lFound = 0U;

        /* Loop through every value available */
        for(const auto &lElmt : getValues(pSection)) {
            if(lExpectedElmt == lElmt) {
                if(lFound) {
                    std::cout << "[WARN ] <EDS::check> Value " << lExpectedElmt << " found " << lFound + 1U << " times" << std::endl;
                }
                ++lFound;
            }
        }

        if(0U == lFound) {
            std::cerr << "[ERROR] <EDS::check> Missing value " << lExpectedElmt << " for section [" << pSection << "]" << std::endl;
            lResult = -1;
        }
    }

    return lResult;
}

int EDS::checkRecommendedKeys(const std::vector<std::string> &pKeys, const std::string &pSection) const {
    int lResult = 0;
    for(const auto &lElmt : pKeys) {
        if(!keyExists(lElmt, pSection)) {
            std::cerr << "[WARN ] <EDS::check> Missing key " << lElmt << " for section [" << pSection << "]" << std::endl;
            lResult = -1;
        }
    }

    return lResult;
}

int EDS::checkIndexes(void) const {
    int         lResult           = 0;
    int         lError            = 0;
    uint16_t    lIdx              = 0U;
    uint8_t     lSubIdx           = 0U;

    /* Map key is the entry's index.
     * The Value is a pair containing :
     * - First the expected number of subs
     * - Second is current sub counter
     * */
    std::map<uint16_t, std::pair<uint8_t, uint8_t>> lNbOfSubs;

    /* Check every index and subindex */
    for(const auto &lElmt : mSectionOrder) {

        if(isIndexSection(lElmt, &lIdx)) {
            lResult = checkIdx(lElmt);

            /* New index. Unicity checked by parent INI class */
            lNbOfSubs.insert(std::pair<uint16_t, std::pair<uint8_t, uint8_t>>(lIdx, std::pair<uint8_t, uint8_t>(0U, 0U)));
            if(0 != (lResult = getUInt8("SubNumber", lNbOfSubs.at(lIdx).first, lElmt))) {
                std::cerr << "[ERROR] <EDS::checkIndexes> (" << lElmt << ") Get SubNumber failed" << std::endl;
            } else {
                std::cout << "[DEBUG] <EDS::checkIndexes> (" << lElmt << ") SubNumber = " << lNbOfSubs.at(lIdx).first << std::endl;
            }
        } else if (isSubIdxSection(lElmt, &lIdx, &lSubIdx)) {
            lResult = checkSubIdx(lElmt, lIdx, lSubIdx);
            
            try {
                ++lNbOfSubs.at(lIdx).second;
                if(lNbOfSubs.at(lIdx).first < lNbOfSubs.at(lIdx).second) {
                    std::cerr << "[ERROR] <EDS::checkIndexes> (" << lElmt << ") To many sub-indexes compared to SubNumber" << std::endl;
                    std::cerr << "        Sub counter = " << (uint16_t)lNbOfSubs.at(lIdx).second << ", Expected sub count = " << (uint16_t)lNbOfSubs.at(lIdx).first << std::endl;
                }
            } catch(const std::exception &e) {
                std::cerr << "[ERROR] <EDS::checkIndexes> lNbOfSubs.at failed : " << e.what() << std::endl;
            }
        } else {
            /* This section is neither an Index nor a SubIndex */
            continue;
        }

        /* Record an error if there is one,
         * but continue checking the other indexes for logs */
        if(0 == lError && 0 != lResult) {
            lError = lResult;
        }
    }

    return lError;
}

int EDS::checkIdx(const std::string &pSection) const {
    /* check if the index is a single entry or if it has sub-indexes */
    uint8_t lNbSubIdx = 0U;
    if(keyExists("SubNumber")) {
        if(0 != getUInt8("SubNumber", lNbSubIdx, pSection)) {
            std::cerr << "[ERROR] <EDS::checkIdx> (" << pSection << ") Get SubNumber failed" << std::endl;
            return -1;
        }
    }

    if(0 == lNbSubIdx) {
        /* Same as a sub-index */
        return checkSubIdx(pSection);
    }

    /* Check for mandatory keys */
    const std::vector<std::string> lMandatoryKeys {
        "ParameterName",
        "ObjectType",
        "SubNumber"
    };
    if(0 != checkMandatoryKeys(lMandatoryKeys, pSection)) {
        //std::cerr << "[ERROR] <EDS::checkIdx> Missing keys for [FileInfo] section" << std::endl;
        return -1;
    }

    /* Check ParameterName length */
    std::string lParamName;
    if(0 != getString("ParameterName", lParamName, pSection)) {
        std::cerr << "[ERROR] <EDS::checkIdx> (" << pSection << ") Get ParameterName failed" << std::endl;
        return -1;
    }

    if(241U < lParamName.size()) {
        std::cerr << "[ERROR] <EDS:checkIdx> (" << pSection << ") ParameterName too long" << std::endl;
        return -1;
    }

    return 0;
}

int EDS::checkSubIdx(const std::string &pSection, const uint16_t &pIdx, const uint8_t &pSubIdx) const {
    (void)pSection;

    return 0;
}

int EDS::check(void) const {
    /* Empty for now */

    /* Check for mandatory sections : 
     * - FileInfo
     * - Comments
     * - DeviceInfo
     * - DummyUsage
     * - ManufacturerObjects
     * - OptionalObjects
     * - 1000 (Device Type)
     * - 1001 (Error Register)
     * - 1018 (Identity Object)
     * 
     * Madantory if HB :
     * - 1017 (Producer HB time)
     * else :
     * - 100C (Guard Time)
     * - 100D (Life Time Factor)
     */
    
    if(sectionExists("FileInfo")) {
        /* Check for mandatory keys */
        const std::vector<std::string> lMandatoryKeys {
            "FileName",
            "FileVersion",
            "FileRevision",
            "EDSVersion",
            "Description",
            "CreationTime",
            "CreationDate",
            "CreatedBy"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("FileInfo"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [FileInfo] section" << std::endl;
            return -1;
        }

        /* Check for recommended keys */
        const std::vector<std::string> lRecommendedKeys {
            "ModificationTime",
            "ModificationDate",
            "ModifiedBy"
        };
        (void)checkRecommendedKeys(lRecommendedKeys, std::string("FileInfo"));
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [FileInfo] section" << std::endl;
        return -1;
    }

    if(sectionExists("Comments")) {
        /* Check for mandatory keys */
        /* None */

        /* Check for recommended keys */
        const std::vector<std::string> lRecommendedKeys {
            "Lines"
        };
        (void)checkRecommendedKeys(lRecommendedKeys, std::string("Comments"));
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [Comments] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("DeviceInfo")) {
        /* Check for mandatory keys */
        const std::vector<std::string> lMandatoryKeys {
            "VendorName",
            "VendorNumber",
            "ProductName",
            "ProductNumber",
            "RevisionNumber",
            "OrderCode",
            "BaudRate_10",
            "BaudRate_20",
            "BaudRate_50",
            "BaudRate_125",
            "BaudRate_250",
            "BaudRate_500",
            "BaudRate_800",
            "BaudRate_1000",
            "SimpleBootUpMaster",
            "SimpleBootUpSlave",
            "Granularity",
            "DynamicChannelsSupported",
            "GroupMessaging",
            "NrOfRXPDO",
            "NrOfTXPDO",
            "LSS_Supported"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("DeviceInfo"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [DeviceInfo] section" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [DeviceInfo] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("DummyUsage")) {
        /* Check for mandatory keys */
        const std::vector<std::string> lMandatoryKeys {
            "Dummy0001",
            "Dummy0002",
            "Dummy0003",
            "Dummy0004",
            "Dummy0005",
            "Dummy0006",
            "Dummy0007"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("DummyUsage"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [DummyUsage] section" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [DummyUsage] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("MandatoryObjects")) {
        /* Check for mandatory keys */
        const std::vector<std::string> lMandatoryKeys {
            "SupportedObjects"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("MandatoryObjects"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [MandatoryObjects] section" << std::endl;
            return -1;
        }

        /* Check for mandatory values */
        const std::vector<std::string> lMandatoryValues {
            "0x1000",
            "0x1001",
            "0x1018" /* (if CANOpen version >= 4.0) */
        };
        if(0 != checkMandatoryValues(lMandatoryValues, std::string("MandatoryObjects"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing values for [MandatoryObjects] section" << std::endl;
            return -1;
        }
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [MandatoryObjects] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("OptionalObjects")) {
        /* Check for mandatory keys :
         * SupportedObjects
         * 
         * Check values :
         * Nothing in the 0x2000-0x5FFF range
         */
        const std::vector<std::string> lMandatoryKeys {
            "SupportedObjects"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("OptionalObjects"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [OptionalObjects] section" << std::endl;
            return -1;
        }
        for(const auto &lElmt : mSectionElementOrder.at("OptionalObjects")) {
            if("SupportedObjects" != lElmt) {
                /* Check if the indexes are not in the 0x2000-0x5FFF range */
                const uint16_t lIdx = std::stoul(lElmt, nullptr, 16);
                if(0x2000U <= lIdx && 0x5FFFU >= lIdx) {
                    std::cerr << "[ERROR] <EDS::check> Manufacturer object in [OptionalObjects]" << std::endl;
                    return -1;
                }
            } else {
                /* Ignore the SupportedObjects key */
            }
        }
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [OptionalObjects] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("ManufacturerObjects")) {
        /* Check for mandatory keys :
         * SupportedObjects
         * 
         * Check values :
         * Nothing out of the 0x2000-0x5FFF range
         */
        const std::vector<std::string> lMandatoryKeys {
            "SupportedObjects"
        };
        if(0 != checkMandatoryKeys(lMandatoryKeys, std::string("ManufacturerObjects"))) {
            //std::cerr << "[ERROR] <EDS::check> Missing keys for [ManufacturerObjects] section" << std::endl;
            return -1;
        }
        for(const auto &lElmt : mSectionElementOrder.at("ManufacturerObjects")) {
            if("SupportedObjects" != lElmt) {
                /* Check if the indexes are not out of the 0x2000-0x5FFF range */
                const uint16_t lIdx = std::stoul(lElmt, nullptr, 16);
                if(0x2000U > lIdx && 0x5FFFU < lIdx) {
                    std::cerr << "[ERROR] <EDS::check> Non manufacturer specific object in [ManufacturerObjects]" << std::endl;
                    return -1;
                }
            } else {
                /* Ignore the SupportedObjects key */
            }
        }
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [ManufacturerObjects] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("1000")) {
        /* Check for mandatory keys */
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [1000] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("1001")) {
        /* Check for mandatory keys */
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [1001] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("1018")) {
        /* Check for mandatory keys */
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [1018] section" << std::endl;
        return -1;
    }
    
    if(sectionExists("1017")) {
        /* Check for mandatory keys */
    } else {
        std::cerr << "[ERROR] <EDS::check> Missing [1017] section" << std::endl;
        std::cerr << "                     Checking for [100C] && [100D]" << std::endl;
        /* Producer hartbeat is absent,
         * check for Node Guarding entries */
        if(sectionExists("100C")) {
            if(sectionExists("100D")) {
                /* Check for mandatory keys */
            } else {
                std::cerr << "[ERROR] <EDS::check> Missing [100D] section" << std::endl;
                return -1;
            }
        } else {
            std::cerr << "[ERROR] <EDS::check> Missing [100C] section" << std::endl;
            return -1;
        }
    }

    /* Check every index and subindex */
    if(0 != checkIndexes()) {
        std::cerr << "[ERROR] <EDS::check> checkIndexes failed" << std::endl;
    }

    /* Each line must be 255 characters max */

    return 0;
}
