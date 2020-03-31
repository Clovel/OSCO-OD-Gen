/**
 * @brief EDS file class
 * 
 * @file EDS.hpp
 */

#ifndef EDS_HPP
#define EDS_HPP

/* Includes -------------------------------------------- */
#include "INI.hpp"

#include "APIExports.h"

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* EDS exception --------------------------------------- */
class EDSException : public INIException {
    virtual const char *what(void) const throw()
    {
        return "EDS file exception occured !";
    }
};

/* EDS class ------------------------------------------- */
class API_EXPORT EDS : public INI {
    public:
        EDS(const std::string &pFile);

        virtual ~EDS();

        /* EDS Checker */
        int check(void) const;

        /* Getters */
        const std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> *odEntries(void) const;

        /* Setters */
    protected:
        /* EDS management */
        int reorderEDSSections(void);

        /* Getters */
        std::vector<std::string> getSubIdxList(const uint16_t &pIdx) const;
        std::vector<std::string> getSubIdxList(const std::string &pIdx) const;
    private:
        /* EDS Checker */
        int checkMandatoryKeys(const std::vector<std::string> &pKeys, const std::string &pSection = "default") const;
        int checkMandatoryValues(const std::vector<std::string> &pValues, const std::string &pSection = "default") const;
        int checkRecommendedKeys(const std::vector<std::string> &pKeys, const std::string &pSection = "default") const;
        int checkIndexes(void) const;
        int checkIndex(const std::string &pSection) const;
        int checkSubIdx(const std::string &pSection, const uint16_t &pIdx = 0x0000U, const uint8_t &pSubIdx = 0x00U) const;

        /* Class attributes */
        std::vector<std::string> mMandatoryObjectList;      /**< The list of MandatoryObjects, as defined in the EDS file */
        std::vector<std::string> mOptionalObjectList;       /**< The list of OptionalObjects, as defined in the EDS file */
        std::vector<std::string> mManufacturerObjectList;   /**< The list of ManufacturerObjects, as defined in the EDS file */

        /** 
         * @brief EDS data
         * 
         * @details
         * List of objects, indexed by their object index string,
         * holding a list of Subobjects, indexed by their (sub)index string,
         * holding a list of key/value pairs, indexed by their keys.
         * 
         * Objects:
         * - Object0:
         *   - SubObject0: (itself)
         *     - Key0 = value0
         *     - Key1 = value1
         *   - SubObject1:
         *     - Key0 = value0
         *     - Key1 = value1
         *     - Key2 = value2
         *   - SubObject2:
         *     - Key0 = value0
         * - Object1:
         *  ...
         *  ...
         */
        std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> mObjects;

        /* TODO : Use pointers to avoid having several copies of the same data */
};

#endif /* EDS_HPP */