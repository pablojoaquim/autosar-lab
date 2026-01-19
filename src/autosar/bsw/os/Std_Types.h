/**
 * @file Std_Types.h
 * @brief AUTOSAR Standard Types Definition
 * @details Platform-independent type definitions per AUTOSAR standard
 * 
 * Location: src/autosar/bsw/os/Std_Types.h
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/* AUTOSAR standard types */
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef int8_t      sint8;
typedef int16_t     sint16;
typedef int32_t     sint32;
typedef bool        boolean;

/* Standard return type */
typedef uint8 Std_ReturnType;

#define E_OK        ((Std_ReturnType)0x00)
#define E_NOT_OK    ((Std_ReturnType)0x01)

/* Boolean values */
#ifndef TRUE
#define TRUE  ((boolean)true)
#endif

#ifndef FALSE
#define FALSE ((boolean)false)
#endif

/* NULL pointer */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* Standard version info */
typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8  sw_major_version;
    uint8  sw_minor_version;
    uint8  sw_patch_version;
} Std_VersionInfoType;

#endif /* STD_TYPES_H */
