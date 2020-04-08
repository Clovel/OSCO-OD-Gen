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
#include <functional>
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
        /* Types */
        /**
         * @brief Callback type for the REST API methods.
         * 
         * @details A method callback provides a way to build the response
         * to a certain method.
         * 
         * @param[in]   pMsg    The request.
         * @param[out]  pOut    The output string : the response.
         * 
         * @return Returns true if successful, false elsewise
         */
        using methodFct_t = std::function<bool(const std::string &, std::string &)>;

        /* Contructors */
        RESTServer(const std::string &pAddr, const std::string pPort, const std::string &pPath);

        /* Destructor */
        /**
         * @brief The RESTServer class destructor
         */
        virtual ~RESTServer();

        /* Getters */
        std::string address(void) const;
        std::string port(void) const;
        std::string apiPath(void) const;

        methodFct_t getCallback(void) const;
        methodFct_t postCallback(void) const;
        methodFct_t putCallback(void) const;
        methodFct_t delCallback(void) const;

        /* Setters */
        void setGetCallback(const methodFct_t &pFct);
        void setPostCallback(const methodFct_t &pFct);
        void setPutCallback(const methodFct_t &pFct);
        void setDelCallback(const methodFct_t &pFct);

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

        /* REST API callbacks */
        methodFct_t mGetCallback;   /**< REST API GET method callback */
        methodFct_t mPostCallback;  /**< REST API POST method callback */
        methodFct_t mPutCallback;   /**< REST API PUT method callback */
        methodFct_t mDelCallback;   /**< REST API DEL method callback */
};

#endif /* RESTSERVER_HPP */
