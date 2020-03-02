/**
 * @brief EDS file class implementation
 * 
 * @file EDS.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"

#include "INIReader.h"

#include <string>
#include <fstream>
#include <iostream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* EDS class implementation ---------------------------- */
EDS::EDS() {
    mIni = nullptr;
}

EDS::~EDS() {
    if(nullptr != mIni) {
        delete mIni;
    }
}

/* Getters */
std::string EDS::fileName(void) const {
    return mFileName;
}

/* Setters */
int EDS::setFile(const std::string &pFileName) {
    mFileStream.open(pFileName, std::ios::in | std::ios::out);

    /* Check if the file was opened correctly */
    if(!mFileStream.is_open()) {
        /* Failed */
        return -1;
    }

    mFileName = pFileName;

    mFileStream.close();

    return 0;
}

/* Parser */
/**
 * @brief Parses the EDS file and sets it's contents
 * in this EDS object
 */
int EDS::parseEDSFile(const std::string &pFile) {
    mFileStream.open(pFile, std::ios::in | std::ios::out);

    /* Check if the file was opened correctly */
    if(!mFileStream.is_open()) {
        /* Failed */
        std::cerr << "[ERROR] <EDS::parseEDSFile> Failed to open file " << pFile << " !" << std::endl;
        return -1;
    }
    /* Close the file, the INIReader will reopen it */
    mFileStream.close();

    mFileName = pFile;

    /* Create a new ini parser */
    if(nullptr != mIni) {
        /* We already had a INIReader ! */
        delete mIni;
    }

    mIni = new INIReader(mFileName);
    if(0 != mIni->ParseError()) {
        std::cerr << "[ERROR] <EDS::parseEDSFile> INIReader constructor failed (" << mFileName << ") !" << std::endl;
        return -2;
    }

    return 0;
}
