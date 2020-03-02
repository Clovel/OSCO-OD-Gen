/**
 * @brief EDS file class implementation
 * 
 * @file EDS.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"

#include <string>
#include <fstream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* EDS class implementation ---------------------------- */
EDS::EDS() {
    /* Empty */
}

EDS::~EDS() {
    /* Empty */
}

std::string EDS::fileName(void) const {
    return mFileName;
}

int EDS::setFile(const std::string &pFileName) {
    std::fstream lFileStream;
    lFileStream.open(pFileName, std::ios::in | std::ios::out);

    /* Check if the file was opened correctly */
    if(!lFileStream.is_open()) {
        /* Failed */
        return -1;
    }

    mFileName = pFileName;

    lFileStream.close();

    return 0;
}
