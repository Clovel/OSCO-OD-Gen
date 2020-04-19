/**
 * @brief OSCO Object Dictionary generator type conversion functions
 * 
 * @details Some of these are derived from the OSCO stack itself.
 * 
 * @file OSCOTypes.c
 */

/* Includes -------------------------------------------- */
#include "OSCOTypes.h"

/* C++ system */
#include <string.h>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Conversion functions -------------------------------- */
int dataTypeToStr(const OSCOODDataType_t pDataType, char ** const pOut) {
    if(NULL == pOut) return -1;
    
    switch(pDataType) {
        case OD_BASIC_TYPE_BOOLEAN:
            *pOut = "BOOLEAN";
            break;
        case OD_BASIC_TYPE_INTEGER8:
            *pOut = "INTEGER8";
            break;
        case OD_BASIC_TYPE_INTEGER16:
            *pOut = "INTEGER16";
            break;
        case OD_BASIC_TYPE_INTEGER24:
            *pOut = "INTEGER24";
            break;
        case OD_BASIC_TYPE_INTEGER32:
            *pOut = "INTEGER32";
            break;
        case OD_BASIC_TYPE_INTEGER40:
            *pOut = "INTEGER40";
            break;
        case OD_BASIC_TYPE_INTEGER48:
            *pOut = "INTEGER48";
            break;
        case OD_BASIC_TYPE_INTEGER56:
            *pOut = "INTEGER56";
            break;
        case OD_BASIC_TYPE_INTEGER64:
            *pOut = "INTEGER64";
            break;
        case OD_BASIC_TYPE_UNSIGNED8:
            *pOut = "UNSIGNED8";
            break;
        case OD_BASIC_TYPE_UNSIGNED16:
            *pOut = "UNSIGNED16";
            break;
        case OD_BASIC_TYPE_UNSIGNED24:
            *pOut = "UNSIGNED24";
            break;
        case OD_BASIC_TYPE_UNSIGNED32:
            *pOut = "UNSIGNED32";
            break;
        case OD_BASIC_TYPE_UNSIGNED40:
            *pOut = "UNSIGNED40";
            break;
        case OD_BASIC_TYPE_UNSIGNED48:
            *pOut = "UNSIGNED48";
            break;
        case OD_BASIC_TYPE_UNSIGNED56:
            *pOut = "UNSIGNED56";
            break;
        case OD_BASIC_TYPE_UNSIGNED64:
            *pOut = "UNSIGNED64";
            break;
        case OD_BASIC_TYPE_REAL32:
            *pOut = "REAL32";
            break;
        case OD_BASIC_TYPE_REAL64:
            *pOut = "REAL64";
            break;
        case OD_BASIC_TYPE_OCTET_STRING:
            *pOut = "OCTET_STRING";
            break;
        case OD_BASIC_TYPE_VISIBLE_STRING:
            *pOut = "VISIBLE_STRING";
            break;
        case OD_BASIC_TYPE_UNICODE_STRING:
            *pOut = "UNICODE_STRING";
            break;
        case OD_BASIC_TYPE_TIME_OF_DAY:
            *pOut = "TIME_OF_DAY";
            break;
        case OD_BASIC_TYPE_DOMAIN:
            *pOut = "DOMAIN";
            break;
        case OD_COMPLEX_TYPE_PDOCOMMPARAM:
            *pOut = "PDO_COMM_PAR";
            break;
        case OD_COMPLEX_TYPE_PDOMAPPING:
            *pOut = "PDO_MAPPING";
            break;
        case OD_COMPLEX_TYPE_SDOPARAM:
            *pOut = "SDO_PAR";
            break;
        default:
            return -1;
    }

    return 0;
}

int objTypeToStr(const OSCOODObjectType_t pObjType, char ** const pOut) {
    if(NULL == pOut) return -1;
    
    switch(pObjType) {
        case OD_OBJ_TYPE_NULL:
            *pOut = "NULL";
            break;
        case OD_OBJ_TYPE_DOMAIN:
            *pOut = "DOMAIN";
            break;
        case OD_OBJ_TYPE_DEFTYPE:
            *pOut = "DEFTYPE";
            break;
        case OD_OBJ_TYPE_DEFSTRUCT:
            *pOut = "DEFSTRUCT";
            break;
        case OD_OBJ_TYPE_VAR:
            *pOut = "VAR";
            break;
        case OD_OBJ_TYPE_ARRAY:
            *pOut = "ARRAY";
            break;
        case OD_OBJ_TYPE_RECORD:
            *pOut = "RECORD";
            break;
        default:
            return -1;
    }

    return 0;
}

int accessTypeToStr(const OSCOODAccessType_t pAccessType, char ** const pOut) {
    if(NULL == pOut) return -1;

    switch(pAccessType) {
        case OD_ACCESS_TYPE_RO:
            *pOut = "ro";
            break;
        case OD_ACCESS_TYPE_WO:
            *pOut = "wo";
            break;
        case OD_ACCESS_TYPE_RW:
            *pOut = "rw";
            break;
        case OD_ACCESS_TYPE_CONST:
            *pOut = "const";
            break;
        case OD_ACCESS_TYPE_RWW:
            *pOut = "rww";
            break;
        case OD_ACCESS_TYPE_RWR:
            *pOut = "rwr";
            break;
        default:
            *pOut = "rw"; /* Default to RW */
            break;
    }

    return 0;
}

OSCOODAccessType_t strToAccessType(const char * const pStr) {
    if(0 == strcmp("ro", pStr)) {
        return OD_ACCESS_TYPE_RO;
    } else if(0 == strcmp("wo", pStr)) {
        return OD_ACCESS_TYPE_WO;
    } else if(0 == strcmp("rw", pStr)) {
        return OD_ACCESS_TYPE_RW;
    } else if(0 == strcmp("const", pStr)) {
        return OD_ACCESS_TYPE_CONST;
    } else {
        return OD_ACCESS_TYPE_RW; /* Default to RW */
    }
}
