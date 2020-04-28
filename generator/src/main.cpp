/**
 * @brief OSCO-OD-Gen main source file
 * 
 * @file main.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODGenerator.hpp"
#include "OSCONode.hpp"
#include "OSCOOD.hpp"
#include "OSCOODFactory.hpp"

#include "EDS.hpp"

#include "OSCOODREST.hpp"

/* C++ system */
#include <iostream>
#include <string>

/* C system */
#include <cstring>
#include <cstdlib> /* realpath() */

/* Defines --------------------------------------------- */
#define ADDRESS "localhost"

/* Notes ----------------------------------------------- */

/* Variable declaration -------------------------------- */

/* Type definitions ------------------------------------ */

/* Support functions ----------------------------------- */
static void printUsage(const char * const pProgName)
{
    std::cout << "[USAGE] %s" << pProgName << std::endl;
    std::cout << "        <arg1> : REST API port number" << std::endl;
    std::cout << "        <arg2> : EDS file" << std::endl;
    std::cout << "        <arg3> : Template path" << std::endl;
    std::cout << "        <arg4> : Output path" << std::endl;
}

/* ----------------------------------------------------- */
/* Main tests ------------------------------------------ */
/* ----------------------------------------------------- */
int main(const int argc, const char * const * const argv) {
    if ((5 != argc)  || (std::strcmp(argv[1U], "--help") == 0)) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const std::string lAddr = std::string(ADDRESS);
    const std::string lPort = std::string(argv[1U]);
    const std::string lPath = "OSCO-OD-Gen";

    /* TODO : Check if file exists */
    const std::string lEDSFile = std::string(realpath(std::string(argv[2U]).c_str(), nullptr));

    const std::string lTemplatePath = std::string(argv[3U]);
    const std::string lOutputPath   = std::string(argv[4U]);

    /* Generate an OSCO Object Dictionary */
    OSCONode* lNode = OSCOODFactory::buildOSCONode(lEDSFile);
    if(nullptr == lNode) {
        std::cerr << "[ERROR] OSCOODFactory::buildOSCONode failed" << std::endl;

        delete lNode;

        return EXIT_FAILURE;
    } else {
        std::cout << "[INFO ] OSCOODFactory::buildOSCONode successfully created a CANOpen node" << std::endl;
        lNode->setName(lNode->fileName());
        lNode->setSourceFilePath(lEDSFile);
    }

#ifndef RESTSERVER_DISABLED
    /* Set up the REST API Server */
    OSCOODREST *lRESTServer = OSCOODREST::createInstance(lAddr, lPort, lPath);
    lRESTServer->addOD(lNode);

    /* Setup RESTServer to generate OSCO OD C code */
    (void)lRESTServer->setGeneratorSettings(lTemplatePath, lOutputPath);

    /* Open server socket */
    if(!lRESTServer->open()) {
        delete lNode;
        return EXIT_FAILURE;
    }

    std::cout << "[INFO ] Listening for request at: " << lAddr << ":" << lPort << "/" << lPath << std::endl;

    /* Loop for the REST API Server */
    lRESTServer->listen();

    /* Close server */
    if(!lRESTServer->close()) {
        delete lRESTServer;
        delete lNode;
        return EXIT_FAILURE;
    }

    delete lRESTServer;
#endif /* RESTSERVER_DISABLED */

    delete lNode;
    return EXIT_SUCCESS;
}
