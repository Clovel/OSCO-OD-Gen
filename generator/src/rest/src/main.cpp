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

    utility::string_t lPort = U(argv[1U]);
    utility::string_t lAddr = U(ADDRESS);
    lAddr.append(U(":"));
    lAddr.append(lPort);

    web::uri_builder lURI(lAddr);
    lURI.append_path(U("OSCO-OD-Gen/Action"));

    lAddr = lURI.to_uri().to_string();

    gRESTServer = std::unique_ptr<RESTServer>(new RESTServer(lAddr));
    gRESTServer->open().wait();

    std::cout << "[INFO] Listening for request at: " << lAddr << std::endl;

    std::string lLine;
    std::getline(std::cin, lLine);

    gRESTServer->close().wait();

    return EXIT_SUCCESS;
}
