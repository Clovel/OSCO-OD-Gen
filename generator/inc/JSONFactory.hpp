/**
 * @brief JSONFactory class
 * 
 * @file JSONFactory.hpp
 */

#ifndef JSONFACTORY_HPP
#define JSONFACTORY_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* RapidJSON */
#include "rapidjson/document.h"

/* C++ System */
#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOOD;
class OSCONode;
class OSCOODIndex;
class OSCOODSubIndex;
class OSCOODObject;

/* JSONFactory class ----------------------------------- */
/**
 * @brief This class contains static functions to build
 * JSON strings from either an OSCOOD, an OSCONode,
 * an OSCOODIndex or an OSCOODSubIndex as an input.
 * 
 * @warning If all the information needed by the factory
 * is not available in the input object,
 * your object will be incomplete.
 * 
 * @warning The JSONFactory creates pointers with `new`,
 * but it is the user's responsability to delete the allocated
 * memory if necessary.
 * 
 * @details The functions will return "[ERROR OCCURED]" in the result string
 * if something went wrong.
 */
class API_EXPORT JSONFactory {
    public:
        static std::string OSCOODObjectToJSON(const OSCOODObject &pObj, rapidjson::Document * const pDoc = nullptr);
        static std::string OSCOODSubIndexToJSON(const OSCOODSubIndex &pSubIdx, rapidjson::Document * const pDoc = nullptr);
        static std::string OSCOODIndexToJSON(const OSCOODIndex &pIdx, rapidjson::Document * const pDoc = nullptr);
        static std::string OSCOODToJSON(const OSCOOD &pOD, rapidjson::Document * const pDoc = nullptr);
        static std::string OSCONodeToJSON(const OSCONode &pNode, rapidjson::Document * const pDoc = nullptr);
    protected:
    private:
};

#endif /* JSONFACTORY_HPP */
