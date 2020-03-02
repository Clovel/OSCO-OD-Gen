/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"

/* C++ system */
#include <iostream>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void print_usage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
    std::cout << "        <arg1> : EDS file" << std::endl;
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    if ((argc < 2) || (std::strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    /* Create an EDS instance */
    EDS lEDS;

    std::cout << "[DEBUG] Opening EDS file " << argv[1] << std::endl;
    if( 0 != lEDS.parseEDSFile(std::string(argv[1]))) {
        std::cerr << "[ERROR] Failed to open EDS file " << argv[1] << " !" << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cerr << "[ERROR] Successfully opened EDS file " << argv[1] << " !" << std::endl;
    }

    return EXIT_SUCCESS;
}
