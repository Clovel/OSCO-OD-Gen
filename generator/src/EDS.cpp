/**
 * @brief EDS file class implementation
 * 
 * @file EDS.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"
#include "INI.hpp"

#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* EDS class implementation ---------------------------- */
EDS::EDS(const std::string &pFile) : INI(pFile) {
    /* Empty */
}

EDS::~EDS() {
    /* Empty */
}

int EDS::reorderEDSSections(void) {
    /* Empty for now */
}

int EDS::check(void) const {
    /* Empty for now */

    /* Reorder the sections */

}
