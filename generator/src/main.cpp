/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
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

    /* Create an EDS instance */
    EDS *lEDS = nullptr;
    try {
        std::cout << "[DEBUG] Opening EDS file " << argv[1U] << std::endl;
        lEDS = new EDS(lEDSFile);
        std::cout << "[INFO ] Successfully parsed EDS file " << argv[1U] << " !" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to parse EDS file " << argv[1U] << " !" << std::endl;
        return EXIT_FAILURE;
    }

    /* Check the EDS file */
    if(0 == lEDS->check()) {
        std::cout << "[INFO ] EDS file check : OK" << std::endl;
    } else {
        std::cerr << "[ERROR] EDS file check : KO" << std::endl;
        delete lEDS;
        return EXIT_FAILURE;
    }

    /* Generating the same EDS file */
    // std::string lCopyEDSFile = lEDSFile.substr(0U, lEDSFile.find_last_of('.')) + ".copy.ini";
    // std::cout << "[DEBUG] lCopyEDSFile = " << lCopyEDSFile << std::endl;
    // if(0 > lEDS->generateFile(lCopyEDSFile)) {
    //     std::cerr << "[ERROR] Failed to generate copy if ini file ! " << std::endl;
    //     delete lEDS;
    //     return EXIT_FAILURE;
    // }

    delete lEDS;
    return EXIT_SUCCESS;
}
