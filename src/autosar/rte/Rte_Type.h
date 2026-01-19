/**
 * @file Rte_Type.h
 * @brief RTE Type Definitions
 * @details Common data types used across SWCs
 * 
 * Location: src/autosar/rte/Rte_Type.h
 */

#ifndef RTE_TYPE_H
#define RTE_TYPE_H

#include "Std_Types.h"

/* Application data types */
typedef uint32 Rte_DataType_UInt32;
typedef sint32 Rte_DataType_SInt32;
typedef boolean Rte_DataType_Boolean;

/* Application status enumeration */
typedef enum {
    RTE_APP_STATUS_IDLE = 0,
    RTE_APP_STATUS_RUNNING,
    RTE_APP_STATUS_ERROR
} Rte_AppStatusType;

/* Kata result structure */
typedef struct {
    uint32 result;
    boolean valid;
    uint32 timestamp;
} Rte_KataResultType;

#endif /* RTE_TYPE_H */
