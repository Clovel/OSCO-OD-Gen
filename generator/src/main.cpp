/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODFactory.hpp"
#include "OSCOOD.hpp"

#include "EDS.hpp"

#include "OSCOODREST.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* C system */
#include <cstring>

/* Defines --------------------------------------------- */
#define ADDRESS "localhost"

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
#ifndef RESTSERVER_DISABLED
    std::cout << "        <arg1> : REST API port number" << std::endl;
    std::cout << "        <arg2> : EDS file" << std::endl;
#else /* RESTSERVER_DISABLED */
    std::cout << "        <arg1> : EDS file" << std::endl;
#endif /* RESTSERVER_DISABLED */
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
#ifndef RESTSERVER_DISABLED
    if ((argc < 3) || (argc > 3) || (std::strcmp(argv[1U], "--help") == 0)) {
#else /* RESTSERVER_DISABLED */
    if ((argc < 2) || (argc > 2) || (std::strcmp(argv[1U], "--help") == 0)) {
#endif /* RESTSERVER_DISABLED */
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

#ifndef RESTSERVER_DISABLED
    const std::string lAddr = std::string(ADDRESS);
    const std::string lPort = std::string(argv[1U]);
    const std::string lPath = "OSCO-OD-Gen";

    const std::string lEDSFile = std::string(argv[2U]);
#else /* RESTSERVER_DISABLED */
    const std::string lEDSFile = std::string(argv[1U]);
#endif /* RESTSERVER_DISABLED */

    /* Generate an OSCO Object Dictionary */
    OSCOOD* lOD = OSCOODFactory::buildOSCOOD(lEDSFile);
    if(nullptr == lOD) {
        std::cerr << "[ERROR] OSCOODFactory::buildOSCOOD failed" << std::endl;

        delete lOD;

        return EXIT_FAILURE;
    } else {
        std::cout << "[INFO ] OSCOODFactory::buildOSCOOD successfully created an Object Dictionary" << std::endl;
        lOD->setName(lOD->fileName());
    }

#ifndef RESTSERVER_DISABLED
    /* Set up the REST API Server */
    OSCOODREST *lRESTServer = OSCOODREST::createInstance(lAddr, lPort, lPath);
    lRESTServer->addOD(lOD);

    /* Open server socket */
    if(!lRESTServer->open()) {
        delete lOD;
        return EXIT_FAILURE;
    }

    std::cout << "[INFO ] Listening for request at: " << lAddr << ":" << lPort << "/" << lPath << std::endl;

    /* Loop for the REST API Server */
    lRESTServer->listen();

    /* Close server */
    if(!lRESTServer->close()) {
        delete lRESTServer;
        delete lOD;
        return EXIT_FAILURE;
    }

    delete lRESTServer;
#endif /* RESTSERVER_DISABLED */

    delete lOD;
    return EXIT_SUCCESS;
}
