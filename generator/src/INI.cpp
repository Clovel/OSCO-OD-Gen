/**
 * @brief INI class implementation
 * 
 * @file INI.cpp
 */

/* Includes -------------------------------------------- */
#include "INI.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

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
    size_t lDelimPos = pStr.find(pDelim);
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
    return pStr.substr(0U, pStr.find(pDelim));
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

/* INI class ------------------------------------------- */
INI::INI(const std::string &pFile) {
    mFileStream.open(pFile, std::ios::in | std::ios::out);

    /* Check if the file was opened correctly */
    if(!mFileStream.is_open()) {
        std::cerr << "[ERROR] <INI::INI> Failed to open file " << pFile << " !" << std::endl;
        throw INIException();
    }

    /* Set default section name */
    std::string lSection = "default";

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
                      << lLineCount << " !" << std::endl;
            throw INIException();
        }

        /* Check if this line is a comment */
        if('#' == lKey[0U] || ';' == lKey[0U]) {
            /* This is a comment */
            std::cout << "[DEBUG] <INI::INI> (" << lLineCount 
                      << ") This is a comment" << std::endl;
            continue;
        }

        /* Check if the is a section name */
        if('[' == lKey[0U]) {
            /* The section tag is [tag] */
            size_t lPos = lKey.find_first_of(']');
            if(std::string::npos == lPos) {
                /* End og tag not found, this INI file is corrupt */
                std::cerr << "[ERROR] <INI::INI> Found unclosed section tag at line " 
                          << lLineCount << " !" << std::endl;
                throw INIException();
            }

            /* Get the section name */
            lSection = lKey.substr(1, lPos - 1);
            continue;
        }

        /* Now, try to extract the name/value pair */
        std::vector<std::string> lKeyValue = split(lKey, '=');

        if(2U != lKeyValue.size()) {
            std::cerr << "[ERROR] <INI::INI> Invalid key/name pair at line "
                      << lLineCount << " !" << std::endl;
            throw INIException();
        }

        /* We got a valid keyvalue pair */
        lKey   = getStrBeforeDelim(lKeyValue[0U], ' ');
        lValue = getStrAfterDelim(lKeyValue[1U], ' ');

        /* Check if there are any more spaces */
        if(std::string::npos != lKey.find(' ')) {
            std::cerr << "[ERROR] <INI::INI> Space in key at line "
                    << lLineCount << std::endl;
            throw INIException();
        }

        if(std::string::npos != lValue.find(' ')) {
            std::cerr << "[ERROR] <INI::INI> Space in value at line "
                    << lLineCount << std::endl;
            throw INIException();
        }

        /* Save our entry */
        mSections[lSection][lKey] = lValue;
        std::cout << "[INFO ] <INI::INI> [" << lSection << "] " << lKey << " = " << mSections.at(lSection).at(lKey) << std::endl;
    }

    std::cout << "[INFO ] <INI::INI> Parsed INI file " << pFile << " successfully !" << std::endl;
}

INI::~INI() {
    /* Empty for now */
}
