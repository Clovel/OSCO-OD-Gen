/**
 * @brief EDS file class
 * 
 * @file EDS.hpp
 */

#ifndef EDS_HPP
#define EDS_HPP

/* Includes -------------------------------------------- */
#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* EDS class ------------------------------------------- */
class EDS {
    public:
        EDS();

        virtual ~EDS();

        /* Getters */
        std::string fileName(void) const;

        /* Setters */
        int setFile(const std::string &pFileName);
    protected:
        std::string mFileName;

    private:
};

#endif /* EDS_HPP */