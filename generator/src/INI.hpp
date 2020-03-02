/**
 * @brief INI class
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
#include <exception>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* INI file exception class ---------------------------- */
class INIException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "INI file exception occured !";
    }
};

/* INI class ------------------------------------------- */
class INI {
    public:
        INI(const std::string &pFile);

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
        int parseFile(const std::string &pFile);
    protected:
        std::string mFileName;
        std::fstream mFileStream;

        std::map<std::string, std::map<std::string, std::string>> mSections;

    private:
};

#endif /* INI_HPP */
