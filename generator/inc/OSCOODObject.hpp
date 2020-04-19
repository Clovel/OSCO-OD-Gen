/**
 * @brief OSCOODObject class
 * 
 * @file OSCOODObject.hpp
 */

/* TODO : Implement CompactSubObj specific behaviors.
 * TODO : Implement ObjFlags specific behaviors.
 */

#ifndef OSCOODOBJECT_HPP
#define OSCOODOBJECT_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

#include "OSCOTypes.h"

/* C++ system */
#include <string>

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOODObject class ---------------------------------- */

/**
 * @brief Class representing an object in a CANOpen Object Dictionary
 */
class API_EXPORT OSCOODObject {
    public:
        /* Constructors */
        OSCOODObject();

        /* Desctructor */
        virtual ~OSCOODObject();

        /* Getters */
        uint8_t            subNumber(void) const;
        std::string        paramName(void) const;
        OSCOODObjectType_t objectType(void) const;
        OSCOODDataType_t   dataType(void) const;
        OSCOODAccessType_t accessType(void) const;
        std::string        defaultValue(void) const;
        std::string        lowLimit(void) const;
        std::string        highLimit(void) const;
        bool               pdoMapping(void) const;
        uint32_t           objFlags(void) const;
        uint8_t            compactSubObj(void) const;

        /* Setters */
        void setSubNumber(const uint8_t &pSubNb);
        void setParamName(const std::string &pParamName);
        void setObjectType(const OSCOODObjectType_t &pObjType);
        void setDataType(const OSCOODDataType_t &pDataType);
        void setAccessType(const OSCOODAccessType_t &pAccessType);
        void setDefaultValue(const std::string &pDefaultValue);
        void setLowLimit(const std::string &pLowLimit);
        void setHighLimit(const std::string &pHighLimit);
        void allowPDOMapping(void);
        void forbidPDOMapping(void);
        void setObjFlags(const uint32_t &pObjFlags);
        void setCompactSubObj(const uint8_t &pCompactSubObj);
        
    protected:
    private:
        /**
         * @brief Number of sub-indexes. 0 if there are none or if this i a sub-index
         * 
         * @details shall indicate the number of sub-indexes available at this index (Unsigned8), 
         * not counting sub-index FFh. 
         * This may be used for the description of sub-objects as defined below. 
         * This entry may be empty or missing, if no sub-objects exist.
         */
        uint8_t            mSubNumber;
        std::string        mParamName; /**< Name of the OD entry (up to 241 characters). */
        OSCOODObjectType_t mObjectType; /**< Shall indicate the object code */
        OSCOODDataType_t   mDataType; /**< Shall indicate the index of the data type of the object in the object dictionary */
        /**
         * @brief Access type/rights for this object, represented by the following strings 
         * - „ro“ - read only,
         * - „wo“ - write only,
         * - „rw“ - read/write,
         * - „rwr“ - read/write on process input,
         * - „rww“ - read/write on process output,
         * - „const“ - constant value
         */
        OSCOODAccessType_t mAccessType;
        std::string mDefaultValue; /**< Shall indicate the default value for this object, */
        std::string mLowLimit; /**< Shall indicate the lowest limit of the object value (only if applicable). */
        std::string mHighLimit; /**< Shall indicate the upper limit of the object value (only if applicable). */
        bool        mPDOMapping; /**< Shall indicate, if it is possible to map this object into a PDO (Boolean, 0 = not mappable, 1 = mappable). */

        /**
         * @brief Special flags for the objects configuration (EDS/DCF specificities)
         * @details These special objects are marked in the EDS and DCF files.
         * The object description sections may contain an entry ObjFlags with an unsigned32 content:
         * The lowest bit shall be a boolean value (0=false, 1=true) for "Refuse write on download",
         * the second bit shall be a boolean value for "Refuse read on scan",
         * the other bits are reserved for further use by CiA and have to be 0.
         * 
         * If the entry is missing, this equals having the value 0. 
         * It is recommended to write the entry in the EDS/DCF only if it is not 0.
         * This avoids unnecessary increase of the file size.
         */
        uint32_t    mObjFlags;

        /**
         * @brief Most often all sections of the sub-indexes of an array are equal except the name. 
         * It is allowed to describe only a template in the main object. 
         * For this the additional unsigned8 entry CompactSubObj may be added.
         * 
         * @details If this entry exists and contains a value not equal to 0, then
         * - the names are assumed to be xxxn with xxx as the name of the main object and n as the decimal sub-index.
         *   Sub-index 00h shall own the Name NrOfObjects
         * - the object types are assumed to be VAR
         * - the data type for all sub-indexes except 00h and FFh is indicated by the entry DataType of the
         *   main object. Sub-index 00h shall always own the data type unsigned8.
         * - the limits are assumed to be NONE
         * - the access type for all sub-indexes except 00h and FFh is indicated by the entry AccessType of the main object. 
         *   The access type for sub-index 00h is assumed to be ReadOnly.
         * - the default values for all sub-indexes except 00h and FFh is 
         *   indicated by the entry DefaultValue of the main object. 
         *   The default value for sub-index 00h is the number given by CompactSubObj.
         * - the entry PDOMapping for all sub-indexes except 0 and 255 is 
         *   given by the entry PDOMapping of the main object. Sub-index 0 is assumed not to be mappable.
         * - It shall be assumed, that the sub-index list does not contain any gaps.
         * 
         * If CompactSubObj is used, the entry SubNumber is not supported, it shall be 0, empty or not appear.
         */
        uint8_t     mCompactSubObj;


};

#endif /* OSCOODOBJECT_HPP */