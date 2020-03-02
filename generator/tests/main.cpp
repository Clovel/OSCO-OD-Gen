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
    std::cout << "[USAGE] %s test#" << pProgName << std::endl;
    std::cout << "        Test -1 : default/no test" << std::endl;
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    /* Test function initialization */
    int32_t lTestNum;
    int16_t lResult = 0;

    if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return -1;
    }

    lTestNum = strtol(argv[1], NULL, 10);

    std::cout << "[TEST ] Executing test #%d" << lTestNum << std::endl;

    /* Executing test */
    switch (lTestNum) {
        default:
            (void)lResult;
            std::cout << "[INFO ] test #%d not available" << lTestNum << std::endl;
            fflush(stdout);
            break;
    }

    return EXIT_SUCCESS;
}
