/**
 * @brief OSCOODSubIndex class
 * 
 * @file OSCOODSubIndex.hpp
 */

#ifndef OSCOODSUBINDEX_HPP
#define OSCOODSUBINDEX_HPP

/* Includes -------------------------------------------- */
#include "OSCOODObject.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODSubIndex class -------------------------------- */
class API_EXPORT OSCOODSubIndex : public OSCOODObject {
    public:
        /* Constructors */
        OSCOODSubIndex();
        OSCOODSubIndex(const uint16_t &pIndex, const uint8_t &pSubIndex);

        /* Destructors */
        virtual ~OSCOODSubIndex();

        /* Getters */
        uint16_t index(void) const;
        uint8_t subIndex(void) const;

        /* Setters */
        void setIndex(const uint16_t &pIndex);
        void setSubIndex(const uint8_t &pSubIndex);
    protected:
    private:
        uint16_t mIndex;
        uint8_t mSubIndex;
};

#endif /* OSCOODSUBINDEX_HPP */