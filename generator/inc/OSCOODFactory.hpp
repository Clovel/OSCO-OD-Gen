/**
 * @brief OSCOODFactory class
 * 
 * @file OSCOODFactory.hpp
 */

#ifndef OSCOODFACTORY_HPP
#define OSCOODFACTORY_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* C++ System */
#include <filesystem>
#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOOD;
class OSCONode;

/* OSCOODFactory class --------------------------------- */
/**
 * @brief This class contains static functions to build
 * either an OSCOOD or a OSCONode from an input file.
 * 
 * @warning If all the information needed by the class
 * is not available in the file, your object will be incomplete.
 * 
 * @warning The OSCOODFactory create the pointers with `new`,
 * but it is the user's responsability to delete the allocated
 * memory if necessary.
 */
class API_EXPORT OSCOODFactory {
    public:
        /* Builders */
        static OSCOOD   *buildOSCOOD(const std::filesystem::path &pFile);
        static OSCONode *buildOSCONode(const std::filesystem::path &pFile);
    protected:
        /* OSCOOD builders */
        static OSCOOD   *OSCOODFromEDS(const std::filesystem::path &pFile);
        static OSCOOD   *OSCOODFromDCF(const std::filesystem::path &pFile);

        /* OSCONode builders */
        static OSCONode *OSCONodeFromEDS(const std::filesystem::path &pFile);
        static OSCONode *OSCONodeFromDCF(const std::filesystem::path &pFile);
    private:
};

#endif /* OSCOODFACTORY_HPP */