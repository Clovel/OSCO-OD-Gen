/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"
#include "INI.hpp"

/* C++ system */
#include <iostream>

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

    /* Create an EDS instance */
    try {
        std::cout << "[DEBUG] Opening EDS file " << argv[1U] << std::endl;
        INI lINI((std::string(argv[1U])));
        std::cerr << "[ERROR] Successfully parsed EDS file " << argv[1U] << " !" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to parse EDS file " << argv[1U] << " !" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
