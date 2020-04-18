/*
 * @brief Generated OD
 * 
 * @file OSCOGenOD.c
 */

/* Includes -------------------------------------------- */
/* OSCO OD module */
#include "OSCOOD.h"
#include "OSCOGenOD.h"

/* OSCO public includes */
#include "OSCOConfigDefines.h"
#include "OSCOTypes.h"

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Default value declarations -------------------------- */
extern const uint8_t  defValU8[];
extern const uint16_t defValU16[];
extern const uint32_t defValU32[];
extern const uint64_t defValU64[];

/* Object value declarations --------------------------- */
extern const uint8_t  objValU8[];
extern const uint16_t objValU16[];
extern const uint32_t objValU32[];
extern const uint64_t objValU64[];

/* Max value declarations ------------------------------ */
extern const uint8_t  maxValU8[];
extern const uint16_t maxValU16[];
extern const uint32_t maxValU32[];
extern const uint64_t maxValU64[];

/* Min value declarations ------------------------------ */
extern const uint8_t  minValU8[];
extern const uint16_t minValU16[];
extern const uint32_t minValU32[];
extern const uint64_t minValU64[];

/* CANOpen Object Dictionary declaration --------------- */
OSCOODElement_t gOD[OD_OBJECT_COUNT] = {
    @@OD_CONTENT_STRUCTURE_ARRAY@@
};
