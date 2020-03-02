/**
 * @brief INI file class
 * 
 * @file INI.hpp
 */

#ifndef INI_HPP
#define INI_HPP

/* Includes -------------------------------------------- */
#include <string>
#include <fstream>
#include <map>
#include <vector>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forzqrd declarations -------------------------------- */

/* EDS class ------------------------------------------- */
class INI {
    public:
        INI();

        virtual ~INI();

        /* Getters */
        std::string fileName(void) const;

        std::string getValue(const std::string &pSection,
            const std::string &pEntry) const;
        
        std::vector<std::string> getEntries(void) const;
        std::vector<std::string> getSections(void) const;

        /* Setters */
        int setFile(const std::string &pFileName);

        /* Parser */
        int parseEDSFile(const std::string &pFile);
    protected:
        std::string mFileName;
        std::fstream mFileStream;

        std::map<std::string, std::map<std::string, std::string>> mConstents;

        std::map<std::string, std::string> mValues;
        std::vector<std::string> mSections;
        std::map<std::string, std::vector<std::string> *> mFields;

    private:
};

#endif /* INI_HPP */
