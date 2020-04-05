/**
 * @brief C++ REST API test main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "RESTServer.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */
#define ADDRESS "http://localhost"

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */
std::unique_ptr<RESTServer> gRESTServer;

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
    std::cout << "        <arg1> : Localhost port number" << std::endl;
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    if ((argc < 2) || (std::strcmp(argv[1U], "--help") == 0)) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    std::string lAddr = ADDRESS;
    std::string lPort = std::string(argv[1U]);
    std::string lPath = "OSCO-OD-Gen/Action";

    gRESTServer = std::unique_ptr<RESTServer>(new RESTServer(lAddr, lPort, lPath));
    gRESTServer->openWait();

    std::cout << "[INFO] Listening for request at: " << lAddr << ":" << lPort << "/" << lPath << std::endl;

    std::string lLine;
    std::getline(std::cin, lLine);

    gRESTServer->closeWait();

    return EXIT_SUCCESS;
}
