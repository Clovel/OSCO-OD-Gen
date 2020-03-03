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

        int getValue(const std::string &pKey,
            std::string &pOut,
            const std::string &pSection = "default") const;
        
        std::vector<std::string> getSections(void) const;
        std::vector<std::string> getKeys(const std::string &pSection = "default") const;

        int getInteger(const std::string &pKey, int &pValue, const std::string &pSection = "default") const;
        int getUnsigned(const std::string &pKey, unsigned int &pValue, const std::string &pSection = "default") const;
        int getString(const std::string &pKey, std::string &pValue, const std::string &pSection = "default") const;
        int getBoolean(const std::string &pKey, bool &pValue, const std::string &pSection = "default") const;
        int getDouble(const std::string &pKey, double &pValue, const std::string &pSection = "default") const;

        /* Setters */
        int setInteger(const std::string &pKey, const int &pValue, const std::string &pSection = "default");
        int setUnsigned(const std::string &pKey, const unsigned int &pValue, const std::string &pSection = "default");
        int setString(const std::string &pKey, const std::string &pValue, const std::string &pSection = "default");
        int setBoolean(const std::string &pKey, const bool &pValue, const std::string &pSection = "default");
        int setDouble(const std::string &pKey, const double &pValue, const std::string &pSection = "default");

        /* Generator */
        int generateINI(const std::string &pDest) const;
    protected:
        std::string mFileName;
        std::fstream mFileStream;

        std::map<std::string, std::map<std::string, std::string>> mSections;
        std::map<std::string, std::vector<std::string>> mSectionElementOrder;
        std::vector<std::string> mSectionOrder;

    private:
};

#endif /* INI_HPP */
