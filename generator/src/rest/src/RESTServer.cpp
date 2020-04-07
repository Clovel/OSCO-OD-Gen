/**
 * @brief RESTServer class implementation
 * 
 * @file RESTServer.cpp
 */

/* Includes -------------------------------------------- */
#include "RESTServer.hpp"

#include "http_parser.h"
#include "http_parser_callbacks.h"

/* C++ system */
#include <iostream>

/* C errno */
#include <cstring>
#include <cstdlib>
#include <errno.h>

/* C Network */
#include <sys/socket.h> /* socket */
#include <netinet/in.h> /* sockaddr_in */
#include <unistd.h>     /* close */

/* Defines --------------------------------------------- */
#define SERVER_BUFFER_SIZE 4096U

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* Helper functions ------------------------------------ */

/* RESTServer class implementation --------------------- */
/* Contructors */
RESTServer::RESTServer(const std::string &pAddr, const std::string pPort, const std::string &pPath) :
    mAddr(pAddr),
    mPort(pPort),
    mPath(pPath),
    mHttpParser(nullptr),
    mHttpParserSettings(nullptr)
{
    /* Initialize HTTP Parser */
    mHttpParser = (http_parser *)malloc(sizeof(http_parser));
    http_parser_init(mHttpParser, HTTP_REQUEST);

    /* Initialize HTTP Parser settings */
    mHttpParserSettings = (http_parser_settings *)malloc(sizeof(http_parser_settings));
    if(0 != httpParserCallbackInit(mHttpParserSettings)) {
        std::cerr << "[ERROR] <RESTServer::RESTServer> httpParserCallbackInit failed" << std::endl;

        free(mHttpParser);
        free(mHttpParserSettings);

        throw RESTServerException();
    }
}

/* Destructor */
RESTServer::~RESTServer() {
    if(nullptr != mHttpParser) {
        free(mHttpParser);
        mHttpParser = nullptr;
    }

    if(nullptr != mHttpParserSettings) {
        free(mHttpParserSettings);
        mHttpParserSettings = nullptr;
    }
}

/* Getters */
std::string RESTServer::address(void) const {
    return mAddr;
}

std::string RESTServer::port(void) const {
    return mPort;
}

std::string RESTServer::apiPath(void) const {
    return mPath;
}

/* Server management */
bool RESTServer::open(void) {
    /* Create a socket */
    errno = 0;
    int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(0 > mServerSocket) {
        std::cerr << "[ERROR] <RESTServer::open> Failed to create socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Set the socket member variable */
    mServerSocket = lSocket;

    /* Initialisation de la structure sockaddr_in */
    struct sockaddr_in lServerAddrIn;
    std::memset(&lServerAddrIn, 0, sizeof(struct sockaddr_in));
    /* Socket type */
    lServerAddrIn.sin_family = AF_INET;
    /* Accpeted client IP addresses */
    lServerAddrIn.sin_addr.s_addr = INADDR_ANY;
    /* Port */
    lServerAddrIn.sin_port = htons(std::atoi(mPort.c_str()));

    /* Set socket options */
    errno = 0;
    const int lEnableOption = 1;
    if(0 > setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&lEnableOption, sizeof(lEnableOption))) {
        std::cerr << "[ERROR] <RESTServer::open> setsockopt SO_REUSEADDR failed" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }
    if(0 > setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEPORT, (const void *)&lEnableOption, sizeof(lEnableOption))) {
        std::cerr << "[ERROR] <RESTServer::open> setsockopt SO_REUSEPORT failed" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Bind socket */
    errno = 0;
    if(0 > bind(mServerSocket, (const struct sockaddr *)&lServerAddrIn , sizeof(lServerAddrIn))) {
        std::cerr << "[ERROR] <RESTServer::open> Failed to bind socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    return true;
}

bool RESTServer::listen(void) {
    /* Listen for connections */
    errno = 0;
    if(0 > ::listen(mServerSocket, 32)) {
        std::cerr << "[ERROR] <RESTServer::listen> Failed to listen for new connections" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    /* Set up before listening in */
    int lClientSock = 0;
    struct sockaddr_in lClientAddrIn;
    std::memset(&lClientAddrIn, 0, sizeof(struct sockaddr_in));
    socklen_t lsInSize = sizeof(lClientAddrIn);
    char lClientMsg[SERVER_BUFFER_SIZE];

    /* Start listening loop */
    while((lClientSock = accept(mServerSocket, (struct sockaddr *)&lClientAddrIn, &lsInSize))) {
        /* Check if the client is valid */
        if(0 <= lClientSock) {
            /* Read the contents of the message */
            size_t lReadBytes = 0;
            while(0 < (lReadBytes = recv(lClientSock, lClientMsg, SERVER_BUFFER_SIZE, 0))) {
                /* Process the message */
                std::cout << "[DEBUG] <RESTServer::listen> Got message : " << std::endl
                          << lClientMsg << std::endl;
                
                processClientMessage(lClientMsg, lReadBytes);
            }

            /* Close the client's socket */
            errno = 0;
            if(0 > ::close(lClientSock)) {
                std::cerr << "[ERROR] <RESTServer::listen> Failed to close client socket" << std::endl;
                if(0 != errno) {
                    std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
                }

                return false;
            }
        } else {
            std::cerr << "[ERROR] <RESTServer::listen> Failed to accept client connection" << std::endl;
            if(0 != errno) {
                std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
            }

            return false;
        }
    }

    return true;
}

bool RESTServer::close(void) {
    errno = 0;
    if(0 > ::close(mServerSocket)) {
        std::cerr << "[ERROR] <RESTServer::close> Failed to close socket" << std::endl;
        if(0 != errno) {
            std::cerr << "        errno = " << errno << " (" << strerror(errno) << ")" << std::endl;
        }

        return false;
    }

    return true;
}

bool RESTServer::processClientMessage(const char * const pMsg, const size_t &pReadBytes) const {
    /* Set a httpMessage_t var for the HTTP Parser */
    httpMessage_t lHTTPMsg;
    std::memset(&lHTTPMsg, 0, sizeof(httpMessage_t));
    if(0 != httpParserCallbackMessageSetter(&lHTTPMsg)) {
        std::cerr << "[ERROR] <RESTServer::processClientMessage> httpParserCallbackMessageSetter failed" << std::endl;
        return false;
    }

    /* Parse the HTTP request */
    size_t lNParsed = http_parser_execute(mHttpParser, mHttpParserSettings, pMsg, pReadBytes);

    /* Handle errors */
    if(pReadBytes != lNParsed) {
        std::cerr << "[ERROR] <RESTServer::processClientMessage> http_parser_execute : lNParsed (" << lNParsed << ") != pReadBytes (" << pReadBytes << ")" << std::endl;
        return false;
    }

    /* Message should be parsed */
    std::cout << "[DEBUG] <RESTServer::processClientMessage> lHTTPMsg :" << std::endl
        << "        lHTTPMsg.method       : " << lHTTPMsg.method << std::endl
        << "        lHTTPMsg.status_code  : " << lHTTPMsg.status_code << std::endl
        << "        lHTTPMsg.request_path : " << std::string(lHTTPMsg.request_path) << std::endl
        << "        lHTTPMsg.request_uri  : " << std::string(lHTTPMsg.request_uri) << std::endl
        << "        lHTTPMsg.query_string : " << std::string(lHTTPMsg.query_string) << std::endl
        << "        lHTTPMsg.body         : " << std::string(lHTTPMsg.body) << std::endl
        << "        lHTTPMsg.url          : " << std::string(lHTTPMsg.url) << std::endl;

    /* Parse the URL */
    

    return true;
}
