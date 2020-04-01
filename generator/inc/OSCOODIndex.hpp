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

/* C++ system */
#include <map>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOODSubIndex;

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
        std::map<uint8_t, OSCOODSubIndex *> subIndexes(void) const;

        /* Setters */
        void setIndex(const uint16_t &pIndex);
        bool addSubIndex(OSCOODSubIndex *pSubIndex);
        bool removeSubIndex(const OSCOODSubIndex * const pSubIndex);
        bool removeSubIndex(const uint8_t &pSubIndex);
    protected:
    private:
        uint16_t mIndex;
        std::map<uint8_t, OSCOODSubIndex *> mSubObjects;
};

#endif /* OSCOODINDEX_HPP */