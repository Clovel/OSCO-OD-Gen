/**
 * @brief OSCOODIndex class
 * 
 * @file OSCOODIndex.hpp
 */

#ifndef OSCOODINDEX_HPP
#define OSCOODINDEX_HPP

/* Includes -------------------------------------------- */
#include "OSCOODObject.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODIndex class ----------------------------------- */
class API_EXPORT OSCOODIndex : OSCOODObject {
    public:
        /* Constructors */
        OSCOODIndex();
        OSCOODIndex(const uint16_t &pIndex);

        /* Destructors */
        virtual ~OSCOODIndex();

        /* Getters */
        uint16_t index(void) const;

        /* Setters */
        void setIndex(const uint16_t &pIndex);
    protected:
    private:
        uint16_t mIndex;
};

#endif /* OSCOODINDEX_HPP */