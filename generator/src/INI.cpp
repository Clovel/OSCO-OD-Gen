/**
 * @brief INI class implementation
 * 
 * @file INI.cpp
 */

/* Includes -------------------------------------------- */
#include "INI.hpp"

/* C++ System */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

/* C System */
#include <cstdlib>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Helper functions ------------------------------------ */
static void split(const std::string &pStr, const char pDelim, std::vector<std::string> &pWords) {
    size_t lPos = 0U, lOldPos = 0U;
    while(std::string::npos != lPos) {
        std::string lSub;

        /* Save the old position in the string */
        lOldPos = lPos;

        /* Find the position of the next '\n' */
        lPos = pStr.find(pDelim, lPos);

        /* Extract the substring (lSub) */
        lSub = pStr.substr(lOldPos, lPos - lOldPos);

        if(std::string::npos != lPos) {
            ++lPos;
        }

        if(lSub.empty()) {
            break;
        }

        pWords.push_back(lSub);
    }
}

static std::vector<std::string> split(const std::string &pStr, char pDelim) {
    std::vector<std::string> lWords;

    split(pStr, pDelim, lWords);

    return lWords;
}

static std::string getStrAfterDelim(const std::string &pStr, char pDelim) {
    size_t lDelimPos = pStr.find_last_of(pDelim);
    size_t lEOLPos   = pStr.find('\n');

    /* Check if we found the delimiter */
    if(std::string::npos == lDelimPos) {
        /* Delimiter is not there, simply return the argument */
        return pStr;
    }

    if(std::string::npos != lEOLPos) {
        ++lEOLPos;
    }

    std::string lSub = pStr.substr(lDelimPos, lEOLPos - lDelimPos);

    return lSub;
}

static std::string getStrBeforeDelim(const std::string &pStr, char pDelim) {
    return pStr.substr(0U, pStr.find_first_of(pDelim));
}

static void removeChar(std::string &pStr, const char pChar) {
    size_t lPos = 0U;

    while(std::string::npos != lPos) {
        if(std::string::npos == (lPos = pStr.find(pChar))) {
            break;
        }
        pStr = pStr.substr(0U, lPos) + pStr.substr(lPos + 1U);
    }
}

static void removeFirstChar(std::string &pStr, const char pChar) {
    if(0U == pStr.find(pChar)) {
        pStr = pStr.substr(1U);
    }
}

static void removeTrailingChar(std::string &pStr, const char pChar) {
    if(pChar == pStr[pStr.size() - 1]) {
        pStr = pStr.substr(0U, pStr.size() - 1);
    }
}

static void removeChar(std::vector<std::string> &pStrs, const char pChar) {
    for(size_t i = 0U; i < pStrs.size(); ++i) {
        removeChar(pStrs[i], pChar);
    }
}

/* Private helper functions ---------------------------- */
bool INI::sectionExists(const std::string &pSection) const {
    /* Does this section exist ? */
    return (mSections.end() != mSections.find(pSection));
}

bool INI::keyExists(const std::string &pKey, const std::string &pSection) const {
    /* Does the section and key exist ? 
     * We also check the section here because otherwise
     * the "at" method will throw a out_of_range
     * exception if it soesn't exist. */
    return ((sectionExists(pSection))
        && (mSections.at(pSection).end() != mSections.at(pSection).find(pKey)));
}


/* INI class ------------------------------------------- */
INI::INI(const std::string &pFile) {
    mFileStream.open(pFile, std::ios::in | std::ios::out);

    /* Check if the file was opened correctly */
    if(!mFileStream.is_open()) {
        std::cerr << "[ERROR] <INI::INI> Failed to open file " << pFile << std::endl;
        throw INIException();
    }

    /* Set default section name */
    std::string lSection    = "default";
    bool        lNewSection = false;

    /* Parse the INI file */
    uint32_t lLineCount = 0U;
    for(std::string lLine = ""; std::getline(mFileStream, lLine);) {
        std::istringstream lStrStream(lLine);
        std::string lKey, lEq, lValue;

        ++lLineCount;

        /* Get the name out of the string stream.
         * Either it is a section name, a comment
         * or a value */

        /* Check if there is something on this line */
        if(!(lStrStream >> lKey)) {
            /* Got nothing from the stream */
            if(EOF == lStrStream.get()) {
                /* This line is empty or EOF */
                continue;
            }

            /* Something went wrong if you are here */
            std::cerr << "[ERROR] <INI::INI> Unknown parsing error at line "
                      << lLineCount << std::endl;
            mFileStream.close();
            throw INIException();
        }

        /* Check if this line is a comment */
        if('#' == lLine[0U] || ';' == lLine[0U]) {
            /* This is a comment */
            std::cout << "[DEBUG] <INI::INI> (" << lLineCount 
                      << ") This is a comment" << std::endl;
            continue;
        }

        /* Check if the is a section name */
        if('[' == lLine[0U]) {
            /* The section tag is [tag] */
            size_t lPos = lLine.find_first_of(']');
            if(std::string::npos == lPos) {
                /* End og tag not found, this INI file is corrupt */
                std::cerr << "[ERROR] <INI::INI> Found unclosed section tag at line " 
                          << lLineCount << std::endl;
                mFileStream.close();
                throw INIException();
            }

            /* Get the section name */
            lSection = lLine.substr(1, lPos - 1);

            /* Does this section exist already ? */
            if(sectionExists(lSection)) {
                /* This section already exists ! */
                std::cerr << "[ERROR] <INI::INI> Duplicate Section in INI file at line " << lLineCount << std::endl;
                mFileStream.close();
                throw INIException();
            }

            /* Save the section in the section order vector */
            mSectionOrder.push_back(lSection);

            lNewSection = true;
            continue;
        }

        /* Now, try to extract the name/value pair */
        std::vector<std::string> lKeyValue = split(lLine, '=');

        if(2U != lKeyValue.size()) {
            std::cerr << "[ERROR] <INI::INI> Invalid key/name pair at line "
                      << lLineCount << std::endl;
            mFileStream.close();
            throw INIException();
        }

        /* We got a valid keyvalue pair */
        lKey   = lKeyValue[0U];
        lValue = lKeyValue[1U];

        /* Remove prefix and trailing whitespaces */
        while(' ' == lKey[0U]) {
            removeFirstChar(lKey, ' ');
        }
        while(' ' == lKey[lKey.length() - 1U]) {
            removeTrailingChar(lKey, ' ');
        }
        while(' ' == lValue[0U]) {
            removeFirstChar(lKey, ' ');
        }
        while(' ' == lValue[lValue.length() - 1U]) {
            removeTrailingChar(lKey, ' ');
        }

        /* This is commented because we accept spaces in the keyname */
        // if(std::string::npos != lKey.find(' ')) {
        //     std::cerr << "[ERROR] <INI::INI> Space in key at line "
        //             << lLineCount << std::endl;
        //     mFileStream.close();
        //     throw INIException();
        // }

        /* This is commented because we accept spaces in the value */
        // if(std::string::npos != lValue.find(' ')) {
        //     std::cerr << "[ERROR] <INI::INI> Space in value at line "
        //             << lLineCount << std::endl;
        //     mFileStream.close();
        //     throw INIException();
        // }

        /* Does this key exist already ? 
         * First, we must check if the section exists
         */
        if(!lNewSection) {
            if(keyExists(lKey)) {
                /* This key already exists ! */
                std::cerr << "[ERROR] <INI::INI> Duplicate Key in INI file at line " << lLineCount << std::endl;
                mFileStream.close();
                throw INIException();
            }
        }


        /* Save our entry */
        mSections[lSection][lKey] = lValue;

        /* Save the entry in the order vector */
        mSectionElementOrder[lSection].push_back(lKey);

        lNewSection = false;

        std::cout << "[INFO ] <INI::INI> [" << lSection << "] " << lKey << " = " << mSections.at(lSection).at(lKey) << std::endl;
    }

    std::cout << "[INFO ] <INI::INI> Parsed INI file " << pFile << " successfully !" << std::endl;
    mFileStream.close();
}

INI::~INI() {
    /* Empty for now */
}

std::string INI::fileName(void) const {
    return mFileName;
}

int INI::getValue(const std::string &pKey,
    std::string &pOut,
    const std::string &pSection) const
{
    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check that the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            pOut = mSections.at(pSection).at(pKey);
            return 0;
        }
    }

    return -1;
}

std::vector<std::string> INI::getSections(void) const {
    std::vector<std::string> lSections;

    for(const auto &lElmt : mSections) {
        lSections.push_back(lElmt.first);
    }

    return lSections;
}

std::vector<std::string> INI::getKeys(const std::string &pSection) const {
    std::vector<std::string> lKeys;

    if(mSections.end() != mSections.find(pSection)) {
        for(const auto &lElmt : mSections.at(pSection)) {
            lKeys.push_back(lElmt.first);
        }
    }

    return lKeys;
}

int INI::getInteger(const std::string &pKey, int &pValue, const std::string &pSection) const {
    std::string lVal;

    if(0 > getValue(pKey, lVal, pSection)) {
        /* Key/Value pair not found.
         * This is either because the section is unknown
         * or the key is unknown */
        std::cerr << "[ERROR] <INI::get> Key/value pair not found !" << std::endl;
        return -1;
    }

    /* Cast the value */
    char *lEnd = 0;
    if(std::string::npos != lVal.find("0x")) {
        /* Haxadecimal value */
        pValue = strtol(mSections.at(pSection).at(pKey).c_str(), &lEnd, 16);
    } else {
        pValue = strtol(mSections.at(pSection).at(pKey).c_str(), &lEnd, 10);
    }

    return *lEnd == 0 ? -1 : 0;
}

int INI::getUnsigned(const std::string &pKey, unsigned int &pValue, const std::string &pSection) const {
    std::string lVal;

    if(0 > getValue(pKey, lVal, pSection)) {
        /* Key/Value pair not found.
         * This is either because the section is unknown
         * or the key is unknown */
        std::cerr << "[ERROR] <INI::get> Key/value pair not found !" << std::endl;
        return -1;
    }

    /* Cast the value */
    char *lEnd = 0;
    if(std::string::npos != lVal.find("0x")) {
        /* Haxadecimal value */
        pValue = strtoul(mSections.at(pSection).at(pKey).c_str(), &lEnd, 16);
    } else {
        pValue = strtoul(mSections.at(pSection).at(pKey).c_str(), &lEnd, 10);
    }
    
    return *lEnd == 0 ? -1 : 0;
}

int INI::getString(const std::string &pKey, std::string &pValue, const std::string &pSection) const {
    return getValue(pKey, pValue, pSection);
}

int INI::getBoolean(const std::string &pKey, bool &pValue, const std::string &pSection) const {
    std::string lVal;

    if(0 > getValue(pKey, lVal, pSection)) {
        /* Key/Value pair not found.
         * This is either because the section is unknown
         * or the key is unknown */
        std::cerr << "[ERROR] <INI::get> Key/value pair not found !" << std::endl;
        return -1;
    }

    /* Cast the value */
    if(("true" == mSections.at(pSection).at(pKey))
        || (mSections.at(pSection).at(pKey) == "True")
        || (mSections.at(pSection).at(pKey) == "1"))
    {
        pValue = true;
    } else if ((mSections.at(pSection).at(pKey) == "false")
        || (mSections.at(pSection).at(pKey) == "False")
        || (mSections.at(pSection).at(pKey) == "0"))
    {
        pValue = false;
    } else {
        /* Unexpected value */
        return -1;
    }

    return 0;
}

int INI::getDouble(const std::string &pKey, double &pValue, const std::string &pSection) const {
    std::string lVal;

    if(0 > getValue(pKey, lVal, pSection)) {
        /* Key/Value pair not found.
         * This is either because the section is unknown
         * or the key is unknown */
        std::cerr << "[ERROR] <INI::get> Key/value pair not found !" << std::endl;
        return -1;
    }

    /* Cast the value */
    char *lEnd = 0;
    pValue = strtod(mSections.at(pSection).at(pKey).c_str(), &lEnd);
    return *lEnd == 0 ? -1 : 0;
}


/* Setters */
int INI::setInteger(const std::string &pKey, const int &pValue, const std::string &pSection) {
    std::string lVal = std::to_string(pValue);

    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check if the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            /* The key does exist ! */
            mSections.at(pSection).at(pKey) = lVal;

            return 0;
        }
    }

    return -1;
}

int INI::setUnsigned(const std::string &pKey, const unsigned int &pValue, const std::string &pSection) {
    std::string lVal = std::to_string(pValue);

    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check if the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            /* The key does exist ! */
            mSections.at(pSection).at(pKey) = lVal;

            return 0;
        }
    }

    return -1;
}

int INI::setString(const std::string &pKey, const std::string &pValue, const std::string &pSection) {
    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check if the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            /* The key does exist ! */
            mSections.at(pSection).at(pKey) = pValue;

            return 0;
        }
    }

    return -1;
}

int INI::setBoolean(const std::string &pKey, const bool &pValue, const std::string &pSection) {
    std::string lVal = std::to_string(pValue);

    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check if the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            /* The key does exist ! */
            mSections.at(pSection).at(pKey) = lVal;

            return 0;
        }
    }

    return -1;
}

int INI::setDouble(const std::string &pKey, const double &pValue, const std::string &pSection) {
    std::string lVal = std::to_string(pValue);

    /* Check if the section exists */
    if(mSections.end() != mSections.find(pSection)) {
        /* Check if the key exists */
        if(mSections.at(pSection).end() != mSections.at(pSection).find(pKey)) {
            /* The key does exist ! */
            mSections.at(pSection).at(pKey) = lVal;

            return 0;
        }
    }

    return -1;
}


/* Generator */
int INI::generateFile(const std::string &pDest) const {

    /* Are we overwriting our original INI file ? */
    if(mFileName == pDest) {
        /* Overwrite detectedn not supported for now */
        std::cerr << "[ERROR] <INI::generateFile> Overwrite detectedn not supported for now." << std::endl;
        return -1;
    }

    std::fstream lOutputFileStream(pDest, std::ios::out);
    if(!lOutputFileStream.is_open()) {
        std::cerr << "[ERROR] <INI::generateFile> Failed to open file " << pDest << std::endl;
        return -1;
    }

    /* For each section */
    for(const auto &lSection : mSectionOrder) {
        /* Write the section name */
        lOutputFileStream << "[" << lSection << "]" << std::endl;

        /* For each key in the section */
        for(const auto &lKey : mSectionElementOrder.at(lSection)) {
            /* Write the key, the equal sign and the value */
            lOutputFileStream << lKey << "=" << mSections.at(lSection).at(lKey) << std::endl;
        }

        /* Add an empty line between sections.
         * This will also add an empty line at EOF.
        */
        lOutputFileStream << std::endl;
    }

    std::cout << "[INFO ] <INI::generateFile> Successfully generated INI file " << pDest << std::endl;
    return 0;
}
