/**
 * @brief EDS file class
 * 
 * @file EDS.hpp
 */

#ifndef EDS_HPP
#define EDS_HPP

/* Includes -------------------------------------------- */
#include "INI.hpp"

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* EDS class ------------------------------------------- */
class EDS : public INI {
    public:
        EDS(const std::string &pFile);

        virtual ~EDS();

        int check(void) const;
    protected:
        int reorderEDSSections(void);
    private:
        int checkIfSection(const std::string &pSection) const;
        int checkMandatoryKeys(const std::vector<std::string> &pKeys, const std::string &pSection = "default") const;
        int checkMandatoryValues(const std::vector<std::string> &pValues, const std::string &pSection = "default") const;
        int checkRecommendedKeys(const std::vector<std::string> &pKeys, const std::string &pSection = "default") const;
        int checkIndexes(void) const;
        int checkIdx(const std::string &pSection) const;
        int checkSubIdx(const std::string &pSection, const uint16_t &pIdx = 0x0000U, const uint8_t &pSubIdx = 0x00U) const;
        //int checkMandatorySections
};

#endif /* EDS_HPP */