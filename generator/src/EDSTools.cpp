/**
 * @brief EDS tools class implementation
 * 
 * @file EDSTools.cpp
 */

/* Includes -------------------------------------------- */
#include "EDSTools.hpp"

/* C++ system */
#include <string>
#include <iostream>

/* C system */
#include <cstring> /* std::memset() */

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* Tool functions -------------------------------------- */
bool isIndexSection(const std::string &pSection, uint16_t * const pIdx) {
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

bool isSubIdxSection(const std::string &pSection, uint16_t * const pIdx, uint8_t * const pSubIdx) {
    static const std::string sPattern = "sub";
    uint16_t          lIdx     = 0U;
    uint32_t          lSubIdx  = 0U;

    /* A sub index section contains lPattern */
    const size_t lPos = pSection.find(sPattern);
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

    const std::string lSubIdxStr = pSection.substr(lPos + sPattern.size());

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

bool remove0xPrefix(std::string &pHexStr) {
    static const std::string sPrefix = "0x";

    /* Does the HexString have the "0x" prefix ? */
    const size_t lPos = pHexStr.find(sPrefix);
    if(std::string::npos == lPos) {
        /* Prefix was not found, no change needed */
        return false;
    } else {
        /* Prefix has been found, remove prefix */
        pHexStr = pHexStr.substr(lPos + sPrefix.size());
        return true;
    }
}

bool add0xPrefix(std::string &pHexStr) {
    static const std::string sPrefix = "0x";

    /* Does the HexString have the "0x" prefix ? */
    const size_t lPos = pHexStr.find(sPrefix);
    if(std::string::npos == lPos) {
        /* Prefix was not found, add it */
        pHexStr = sPrefix + pHexStr;
        return true;
    } else {
        /* Prefix has been found, nothing to do */
        return false;
    }
}

std::string uint8ToHexStr(const uint8_t &pInt, const bool &pZeroX) {
    char lChars[5U];
    std::memset(lChars, 0, 5U);
    if(pZeroX) {
        snprintf(lChars, 5U, "0x%02X", pInt);
    } else {
        snprintf(lChars, 5U, "%02X", pInt);
    }

    return std::string(lChars);
}

std::string uint16ToHexStr(const uint16_t &pInt, const bool &pZeroX) {
    char lChars[5U];
    std::memset(lChars, 0, 5U);
    if(pZeroX) {
        snprintf(lChars, 5U, "0x%04X", pInt);
    } else {
        snprintf(lChars, 5U, "%04X", pInt);
    }

    return std::string(lChars);
}

std::string uint32ToHexStr(const uint32_t &pInt, const bool &pZeroX) {
    char lChars[5U];
    std::memset(lChars, 0, 5U);
    if(pZeroX) {
        snprintf(lChars, 5U, "0x%08X", pInt);
    } else {
        snprintf(lChars, 5U, "%08X", pInt);
    }

    return std::string(lChars);
}

std::string uint64ToHexStr(const uint64_t &pInt, const bool &pZeroX) {
    char lChars[5U];
    std::memset(lChars, 0, 5U);
    if(pZeroX) {
        snprintf(lChars, 5U, "0x%16X", pInt);
    } else {
        snprintf(lChars, 5U, "%16X", pInt);
    }

    return std::string(lChars);
}



bool hexStrToUInt8(const std::string &pStr, uint8_t &pInt) {
    bool lResult = false;
    unsigned int lInt = 0U;
    if(1 == std::sscanf(pStr.c_str(), "0x%02X", &lInt)) {
        lResult = true;
    } else if(1 == std::sscanf(pStr.c_str(), "%02X", &lInt)) {
        lResult = true;
    }

    if((0x0000U != (0xFF00U & lInt)) && (0U != lInt)) {
        lResult = false;
    } else {
        pInt = (uint8_t)(0x00FFU & lInt);
    }

    return lResult;
}

bool hexStrToUInt16(const std::string &pStr, uint16_t &pInt) {
    bool lResult = false;
    unsigned int lInt = 0U;
    if(1 == std::sscanf(pStr.c_str(), "0x%04X", &lInt)) {
        lResult = true;
    } else if(1 == std::sscanf(pStr.c_str(), "%04X", &lInt)) {
        lResult = true;
    }

    if(lResult) {
        pInt = (uint16_t)(0xFFFFU & lInt);
    }

    return lResult;
}
