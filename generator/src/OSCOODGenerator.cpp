/**
 * @brief OSCO OD Generator class implementation
 * 
 * @file OSCOODGenerator.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODGenerator.hpp"
#include "OSCOOD.hpp"

/* FileFiller */
#include "FileFiller.hpp"
#include "FileFillerTagFactory.hpp"

/* C++ system */
#include <exception>
#include <iostream>
#include <string>
#include <map>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODGenerator class implementation ---------------- */
int OSCOODGenerator::generate_OSCOGenOD_SourceFiles(const OSCOOD &pOD) {
    int lResult = 0;

    /* Generate main generated OD header */
    if(0 > (lResult = generate_OSCOGenOD_h(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD source file */
    if(0 > (lResult = generate_OSCOGenOD_c(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD default values source file */
    if(0 > (lResult = generate_OSCOGenOD_DefaultValues_c(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD max values source file */
    if(0 > (lResult = generate_OSCOGenOD_MaxValues_c(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD min values source file */
    if(0 > (lResult = generate_OSCOGenOD_MinValues_c(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD value header */
    if(0 > (lResult = generate_OSCOGenOD_Values_c(pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    return 0; /* Or lResult ? */
}

int OSCOODGenerator::generate_OSCOGenOD_h(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_c(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_DefaultValues_c(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_MaxValues_c(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_MinValues_c(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_Values_c(const OSCOOD &pOD) {
    int lResult = 0;

    return lResult;
}
