/**
 * @brief RESTServer class
 * 
 * @file RESTServer.hpp
 */

#ifndef RESTSERVER_HPP
#define RESTSERVER_HPP

/* Includes -------------------------------------------- */
#include <cpprest/http_listener.h>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* RESTServer class ------------------------------------ */
class RESTServer {
    public:
        /* Contructors */
        RESTServer(const std::string &pAddr, const std::string pPort, const std::string &pPath);

        void openWait(void) {
            (void)mListener.open().wait();
        }

        void closeWait(void) {
            (void)mListener.close().wait();
        }

    protected:
        static void handleGet(web::http::http_request pMsg);
        static void handlePut(web::http::http_request pMsg);
        static void handlePost(web::http::http_request pMsg);
        static void handleDelete(web::http::http_request pMsg);
    private:
        web::http::experimental::listener::http_listener mListener;
};

#endif /* RESTSERVER_HPP */
