/**
 * @brief OSCOOD class
 * 
 * @file OSCOOD.hpp
 */

#ifndef OSCOOD_HPP
#define OSCOOD_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* C++ system */
#include <map>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOODIndex;

/* OSCOOD class ---------------------------------- */
class API_EXPORT OSCOOD {
    public:
        /* Constructors */
        OSCOOD();

        /* Destructor */
        virtual ~OSCOOD();

        /* Getters */
        std::map<uint16_t, OSCOODIndex *> indexes(void) const;

        /* Setters */
        bool addIndex(OSCOODIndex *pIndex);
        bool removeIndex(const OSCOODIndex * const pIndex);
        bool removeIndex(const uint16_t &pIndex);
    protected:
    private:
        std::map<uint16_t, OSCOODIndex *> mObjects;
};

#endif /* OSCOOD_HPP */