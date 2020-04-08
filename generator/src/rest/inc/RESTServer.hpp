/**
 * @brief RESTServer class
 * 
 * @file RESTServer.hpp
 */

#ifndef RESTSERVER_HPP
#define RESTSERVER_HPP

/* Includes -------------------------------------------- */
/* C++ system */
#include <exception>
#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* RESTServer exception -------------------------------- */
class RESTServerException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "RESTServer exception occured !";
    }
};

/* RESTServer class ------------------------------------ */
class RESTServer {
    public:
        /* Contructors */
        RESTServer(const std::string &pAddr, const std::string pPort, const std::string &pPath);

        /* Destructor */
        virtual ~RESTServer();

        /* Getters */
        std::string address(void) const;
        std::string port(void) const;
        std::string apiPath(void) const;

        /* Server management */
        bool open(void);
        bool listen(void);
        bool close(void);

    protected:
    private:
        /* Request processing functions */
        bool processClientMessage(const char * const pMsg, const size_t &pReadBytes, const int &pClientSocket) const;
        // bool processGetRequest(const std::string &pMsg) const;
        // bool processPutRequest(const std::string &pMsg) const;
        // bool processPostRequest(const std::string &pMsg) const;
        // bool processDelRequest(const std::string &pMsg) const;

        /* Networking member variables */
        int mServerSocket;

        std::string mAddr;
        std::string mPort;
        std::string mPath;
};

#endif /* RESTSERVER_HPP */
