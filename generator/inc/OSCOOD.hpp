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
#include <vector>
#include <exception>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOODIndex;

/* OSCOOD exception ------------------------------------ */
class OSCOODException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "OSCOOD exception occured !";
    }
};

/* OSCOOD class ---------------------------------- */
class API_EXPORT OSCOOD {
    public:
        /* Constructors */
        OSCOOD();
        OSCOOD(const std::map<uint16_t, OSCOODIndex *> &pObjects);
        OSCOOD(const std::vector<OSCOODIndex *> &pObjects);

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