/**
 * @brief INI class
 * 
 * @file INI.hpp
 */

#ifndef INI_HPP
#define INI_HPP

/* Includes -------------------------------------------- */
/* C++ System */
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <exception>

/* C System */
#include <cstdint>

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

        int getInt64(const std::string &pKey, int64_t &pValue, const std::string &pSection = "default") const;
        int getInt32(const std::string &pKey, int32_t &pValue, const std::string &pSection = "default") const;
        int getInt16(const std::string &pKey, int16_t &pValue, const std::string &pSection = "default") const;
        int getInt8(const std::string &pKey, int8_t &pValue, const std::string &pSection = "default") const;
        int getUInt64(const std::string &pKey, uint64_t &pValue, const std::string &pSection = "default") const;
        int getUInt32(const std::string &pKey, uint32_t &pValue, const std::string &pSection = "default") const;
        int getUInt16(const std::string &pKey, uint16_t &pValue, const std::string &pSection = "default") const;
        int getUInt8(const std::string &pKey, uint8_t &pValue, const std::string &pSection = "default") const;
        int getString(const std::string &pKey, std::string &pValue, const std::string &pSection = "default") const;
        int getBoolean(const std::string &pKey, bool &pValue, const std::string &pSection = "default") const;
        int getDouble(const std::string &pKey, double &pValue, const std::string &pSection = "default") const;

        /* Setters */
        int setInt64(const std::string &pKey, const int64_t &pValue, const std::string &pSection = "default");
        int setInt32(const std::string &pKey, const int32_t &pValue, const std::string &pSection = "default");
        int setInt16(const std::string &pKey, const int16_t &pValue, const std::string &pSection = "default");
        int setInt8(const std::string &pKey, const int8_t &pValue, const std::string &pSection = "default");
        int setUInt64(const std::string &pKey, const uint64_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int setUInt32(const std::string &pKey, const uint32_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int setUInt16(const std::string &pKey, const uint16_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int setUInt8(const std::string &pKey, const uint8_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int setString(const std::string &pKey, const std::string &pValue, const std::string &pSection = "default");
        int setBoolean(const std::string &pKey, const bool &pValue, const std::string &pSection = "default");
        int setDouble(const std::string &pKey, const double &pValue, const std::string &pSection = "default");

        /* Adders */
        int addSection(const std::string &pSection);
        int addInt64(const std::string &pKey, const int64_t &pValue, const std::string &pSection = "default");
        int addInt32(const std::string &pKey, const int32_t &pValue, const std::string &pSection = "default");
        int addInt16(const std::string &pKey, const int16_t &pValue, const std::string &pSection = "default");
        int addInt8(const std::string &pKey, const int8_t &pValue, const std::string &pSection = "default");
        int addUInt64(const std::string &pKey, const uint64_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int addUInt32(const std::string &pKey, const uint32_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int addUInt16(const std::string &pKey, const uint16_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int addUInt8(const std::string &pKey, const uint8_t &pValue, const std::string &pSection = "default", const int &pBase = 10);
        int addString(const std::string &pKey, const std::string &pValue, const std::string &pSection = "default");
        int addBoolean(const std::string &pKey, const bool &pValue, const std::string &pSection = "default");
        int addDouble(const std::string &pKey, const double &pValue, const std::string &pSection = "default");

        /* Generator */
        virtual int generateFile(const std::string &pDest) const;
    protected:
        std::string mFileName;
        std::fstream mFileStream;

        std::map<std::string, std::map<std::string, std::string>> mSections;
        std::map<std::string, std::vector<std::string>> mSectionElementOrder;
        std::vector<std::string> mSectionOrder;

    private:
        bool sectionExists(const std::string &pSection) const;
        bool keyExists(const std::string &pKey, const std::string &pSection = "default") const;
};

#endif /* INI_HPP */
