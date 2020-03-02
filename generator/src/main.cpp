/**
 * @brief OSCO-OD-Gen main test file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include <iostream>

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
    if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
