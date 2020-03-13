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

        int reorderEDSSections(void);
        int check(void) const;
    protected:
    private:
};

#endif /* EDS_HPP */