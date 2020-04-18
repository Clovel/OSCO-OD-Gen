/**
 * @brief OSCO Object Dictionary generator types.
 * 
 * @details Some of these are derived from the OSCO stack itself.
 * 
 * @file OSCOTypes.h
 */

#ifndef OSCOTYPES_H
#define OSCOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes -------------------------------------------- */

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */
typedef enum _odDataTypes {
    OD_UNKNOWN_TYPE                 = 0U,
    OD_BASIC_TYPE_BOOLEAN           = 0x0001U,
    OD_BASIC_TYPE_INTEGER8          = 0x0002U,
    OD_BASIC_TYPE_INTEGER16         = 0x0003U,
    OD_BASIC_TYPE_INTEGER24         = 0x0010U,
    OD_BASIC_TYPE_INTEGER32         = 0x0004U,
    OD_BASIC_TYPE_INTEGER40         = 0x0012U,
    OD_BASIC_TYPE_INTEGER48         = 0x0013U,
    OD_BASIC_TYPE_INTEGER56         = 0x0014U,
    OD_BASIC_TYPE_INTEGER64         = 0x0015U,
    OD_BASIC_TYPE_UNSIGNED8         = 0x0005U,
    OD_BASIC_TYPE_UNSIGNED16        = 0x0006U,
    OD_BASIC_TYPE_UNSIGNED24        = 0x0016U,
    OD_BASIC_TYPE_UNSIGNED32        = 0x0007U,
    OD_BASIC_TYPE_UNSIGNED40        = 0x0018U,
    OD_BASIC_TYPE_UNSIGNED48        = 0x0019U,
    OD_BASIC_TYPE_UNSIGNED56        = 0x001AU,
    OD_BASIC_TYPE_UNSIGNED64        = 0x001BU,
    OD_BASIC_TYPE_REAL32            = 0x0008U,
    OD_BASIC_TYPE_REAL64            = 0x0011U,
    OD_BASIC_TYPE_OCTET_STRING      = 0x000AU,
    OD_BASIC_TYPE_VISIBLE_STRING    = 0x0009U,
    OD_BASIC_TYPE_UNICODE_STRING    = 0x000BU,
    OD_BASIC_TYPE_TIME_OF_DAY       = 0x000CU,
    OD_BASIC_TYPE_DOMAIN            = 0x000FU,
    OD_COMPLEX_TYPE_PDOCOMMPARAM    = 0x0020U,
    OD_COMPLEX_TYPE_PDOMAPPING      = 0x0021U,
    OD_COMPLEX_TYPE_SDOPARAM        = 0x0022U,
    OD_COMPLEX_TYPE_IDENTITY,
    OD_COMPLEX_TYPE_DEBUGGERPARAM,
    OD_COMPLEX_TYPE_CMDPARAM,
    OD_BASIC_TYPE_VOID,
} OSCOODDataType_t;

typedef enum _odObjectTypes {
    OD_OBJ_TYPE_UNKNOWN = 0U,
    /* TODO : Get OD_OBJ_TYPE_NULL value */
    OD_OBJ_TYPE_NULL,           /**< No data fields */
    /* TODO : Get OD_OBJ_TYPE_DOMAIN value */
    OD_OBJ_TYPE_DOMAIN,         /**< A large amount of data */
    /* TODO : Get OD_OBJ_TYPE_DEFTYPE value */
    OD_OBJ_TYPE_DEFTYPE,        /**< Defines a standard data type */
    /* TODO : Get OD_OBJ_TYPE_DEFSTRUCT value */
    OD_OBJ_TYPE_DEFSTRUCT,      /**< Defines a complex data type */
    OD_OBJ_TYPE_VAR = 0x7U,     /**< A single value */
    OD_OBJ_TYPE_ARRAY = 0x8U,   /**< An entry with more than one Subindex, with each Subindex (except 0x00) having the same data type */
    OD_OBJ_TYPE_RECORD = 0x9U,  /**< An entry with more than one Subindex, with each Subindex (except 0x00) having differing data type */
} OSCOODObjectType_t;

typedef enum _odAccessTypes {
    OD_ACCESS_TYPE_UNKNOWN = 0U,
    OD_ACCESS_TYPE_RO,      /**< read only */
    OD_ACCESS_TYPE_WO,      /**< write only */
    OD_ACCESS_TYPE_RW,      /**< read/write */
    OD_ACCESS_TYPE_CONST,   /**< constant value */
    OD_ACCESS_TYPE_RWW,     /**< read/write on process input */
    OD_ACCESS_TYPE_RWR      /**< read/write on process output */
} OSCOODAccessType_t;

/* Conversion functions -------------------------------- */
int dataTypeToStr(const OSCOODDataType_t pDataType, char ** const pOut);
int objTypeToStr(const OSCOODObjectType_t pObjType, char ** const pOut);
int accessTypeToStr(const OSCOODAccessType_t pAccessType, char ** const pOut);
OSCOODAccessType_t strToAccessType(const char * const pStr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OSCOTYPES_H */
