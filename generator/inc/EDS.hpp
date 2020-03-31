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
        int checkIdx(const std::string &pSection) const;
        int checkSubIdx(const std::string &pSection, const uint16_t &pIdx = 0x0000U, const uint8_t &pSubIdx = 0x00U) const;

        /* Class attributes */
        std::vector<std::string> mObjectList;
        std::vector<std::string> mMandatoryObjectList;
        std::vector<std::string> mOptionalObjectList;
        std::vector<std::string> mManufacturerObjectList;

        std::map<std::string, std::vector<std::string>> mObjects;
};

#endif /* EDS_HPP */