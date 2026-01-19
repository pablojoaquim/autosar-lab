/**
 * @file Rte.c
 * @brief AUTOSAR Runtime Environment - Implementation
 * 
 * Location: src/autosar/rte/Rte.c
 * 
 * The RTE routes data between:
 * - SWC ? SWC (same ECU) via SignalRouter
 * - SWC ? Bus (other ECUs) via COM module
 */

#include "Rte.h"
#include "Os.h"
#include "SignalRouter.h"
#include <stdio.h>
#include <string.h>

/* Port mapping to internal signals */
typedef struct {
    uint8 componentId;
    uint8 portId;
    SignalRouter_SignalIdType signalId;
    boolean isInternal;  /* TRUE = internal routing, FALSE = bus communication */
} Rte_PortMappingType;

/* Port mapping table - defines which component ports map to which signals */
static const Rte_PortMappingType port_mapping[] = {
    /* componentId, portId, signalId,         isInternal */
    /* SwcTemplate ports - internal communication */
    {0, 0, SIGNAL_INPUT_A,      TRUE},   /* InputA */
    {0, 1, SIGNAL_INPUT_B,      TRUE},   /* InputB */
    {0, 0, SIGNAL_OUTPUT_RESULT, TRUE},  /* Output */
    
    /* SwcKata001 ports - internal communication */
    {1, 0, SIGNAL_INPUT_A,      TRUE},   /* Input1 */
    {1, 1, SIGNAL_INPUT_B,      TRUE},   /* Input2 */
    {1, 0, SIGNAL_OUTPUT_RESULT, TRUE},  /* Sum */
};

static const uint32 PORT_MAPPING_COUNT = sizeof(port_mapping) / sizeof(port_mapping[0]);

/* Find signal ID for a component port */
static Std_ReturnType Rte_FindSignal(uint8 componentId, uint8 portId, 
                                      boolean isWrite, SignalRouter_SignalIdType* signalId,
                                      boolean* isInternal) {
    for (uint32 i = 0; i < PORT_MAPPING_COUNT; i++) {
        if (port_mapping[i].componentId == componentId && 
            port_mapping[i].portId == portId) {
            *signalId = port_mapping[i].signalId;
            *isInternal = port_mapping[i].isInternal;
            return E_OK;
        }
    }
    return E_NOT_OK;
}

Std_ReturnType Rte_Init(void) {
    printf("[RTE] Initializing Runtime Environment...\n");
    printf("[RTE] Port mappings configured: %u\n", PORT_MAPPING_COUNT);
    printf("[RTE] Internal routing via SignalRouter\n");
    printf("[RTE] External routing via COM module\n");
    return E_OK;
}

Std_ReturnType Rte_Start(void) {
    printf("[RTE] Starting RTE...\n");
    /* SWC runnables are registered with OS and will be called automatically */
    return E_OK;
}

Std_ReturnType Rte_Read(uint8 componentId, uint8 portId, void* data) {
    SignalRouter_SignalIdType signalId;
    boolean isInternal;
    
    if (data == NULL) {
        return E_NOT_OK;
    }
    
    if (Rte_FindSignal(componentId, portId, FALSE, &signalId, &isInternal) != E_OK) {
        return E_NOT_OK;
    }
    
    /* Route based on signal type */
    if (isInternal) {
        /* Internal signal - use SignalRouter */
        return SignalRouter_Read(signalId, (uint32*)data);
    } else {
        /* External signal - use COM module */
        /* In real system: return Com_ReceiveSignal(mapped_com_signal, data); */
        return E_NOT_OK;  /* Not implemented in this lab */
    }
}

Std_ReturnType Rte_Write(uint8 componentId, uint8 portId, const void* data) {
    SignalRouter_SignalIdType signalId;
    boolean isInternal;
    
    if (data == NULL) {
        return E_NOT_OK;
    }
    
    if (Rte_FindSignal(componentId, portId, TRUE, &signalId, &isInternal) != E_OK) {
        return E_NOT_OK;
    }
    
    /* Route based on signal type */
    if (isInternal) {
        /* Internal signal - use SignalRouter */
        return SignalRouter_Write(signalId, *(const uint32*)data);
    } else {
        /* External signal - use COM module */
        /* In real system: return Com_SendSignal(mapped_com_signal, data); */
        return E_NOT_OK;  /* Not implemented in this lab */
    }
}
