/**
 * @brief EDS file class
 * 
 * @file EDS.hpp
 */

#ifndef EDS_HPP
#define EDS_HPP

/* Includes -------------------------------------------- */
#include <string>
#include <fstream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forzqrd declarations -------------------------------- */
class INIReader;

/* EDS class ------------------------------------------- */
class EDS {
    public:
        EDS();

        virtual ~EDS();

        /* Getters */
        std::string fileName(void) const;

        /* Setters */
        int setFile(const std::string &pFileName);

        /* Parser */
        int parseEDSFile(const std::string &pFile);
    protected:
        std::string mFileName;
        std::fstream mFileStream;

        INIReader *mIni;

    private:
};

#endif /* EDS_HPP */