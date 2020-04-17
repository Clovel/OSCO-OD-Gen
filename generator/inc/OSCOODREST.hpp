/**
 * @brief OSCOODREST class
 * 
 * @file OSCOODREST.hpp
 */

#ifndef OSCOODREST_HPP
#define OSCOODREST_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

#include "RESTServer.hpp"

/* C++ system */
#include <map>
#include <vector>
#include <string>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOOD;

/* OSCOOD class ---------------------------------- */
class API_EXPORT OSCOODREST : public RESTServer {
    public:
        /* Create singleton */
        static OSCOODREST *createInstance(const std::string &pAddr, const std::string pPort, const std::string &pPath);
        /* Get singleton */
        static OSCOODREST *instance(void);

        /* Destructors */
        virtual ~OSCOODREST();

        /* Getters */
        std::map<std::string, OSCOOD *> ODs(void) const;
        OSCOOD *OD(const std::string &pName) const;
        bool canGenerateCCode(void) const;
        std::string generatorTemplateFilePath(void) const;
        std::string generatorOutputPath(void) const;

        /* Setters */
        bool addOD(OSCOOD &pOD);
        bool addOD(OSCOOD * const pOD);

        int setGeneratorSettings(const std::string &pTemplateFilePath, const std::string &pOutputPath);
    protected:
    private:
        /* Constructors */
        OSCOODREST(const std::string &pAddr, const std::string pPort, const std::string &pPath);

        /* Object Dictionaries */
        std::map<std::string, OSCOOD *> mObjectDictionaries;

        bool mCanGenerateCCode; /**< Can generate C code */
        std::string mTemplateFilePath; /**< Path to the C code templates */
        std::string mOutputPath; /**< Path to the output directory */

        /* REST Callbacks */
        static HttpStatus OSCOOD_GET(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut);
        static HttpStatus OSCOOD_POST(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut);
        static HttpStatus OSCOOD_PUT(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut);
        static HttpStatus OSCOOD_DEL(const std::string &pPath, const std::vector<std::string> &pQueries, std::string &pOut);
};

#endif /* OSCOODREST_HPP */
