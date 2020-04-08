/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODFactory.hpp"
#include "OSCOOD.hpp"

#include "EDS.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
    std::cout << "        <arg1> : EDS file" << std::endl;
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    if ((argc < 2) || (std::strcmp(argv[1U], "--help") == 0)) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string lEDSFile = std::string(argv[1U]);

    /* Generate an OSCO Object Dictionary */
    OSCOOD* lOD = OSCOODFactory::buildOSCOOD(lEDSFile);
    if(nullptr == lOD) {
        std::cerr << "[ERROR] OSCOODFactory::buildOSCOOD failed" << std::endl;

        delete lOD;

        return EXIT_FAILURE;
    } else {
        std::cout << "[INFO ] OSCOODFactory::buildOSCOOD successfully created an Object Dictionary" << std::endl;
    }

    delete lOD;
    return EXIT_SUCCESS;
}
