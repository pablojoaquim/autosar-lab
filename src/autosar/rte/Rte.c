/**
 * @file Rte.c
 * @brief AUTOSAR Runtime Environment - Implementation
 * 
 * Location: src/autosar/rte/Rte.c
 */

#include "Rte.h"
#include "Os.h"
#include <stdio.h>
#include <string.h>

/* Port mapping to COM signals */
typedef struct {
    uint8 componentId;
    uint8 portId;
    Com_SignalIdType signalId;
} Rte_PortMappingType;

/* Port mapping table */
static const Rte_PortMappingType port_mapping[] = {
    /* SwcTemplate ports */
    {0, 0, COM_SIGNAL_INPUT_A},      /* InputA */
    {0, 1, COM_SIGNAL_INPUT_B},      /* InputB */
    {0, 0, COM_SIGNAL_OUTPUT_RESULT},/* Output */
    
    /* SwcKata001 ports */
    {1, 0, COM_SIGNAL_INPUT_A},      /* Input1 */
    {1, 1, COM_SIGNAL_INPUT_B},      /* Input2 */
    {1, 0, COM_SIGNAL_OUTPUT_RESULT},/* Sum */
};

static const uint32 PORT_MAPPING_COUNT = sizeof(port_mapping) / sizeof(port_mapping[0]);

/* Find signal ID for a component port */
static Std_ReturnType Rte_FindSignal(uint8 componentId, uint8 portId, 
                                      boolean isWrite, Com_SignalIdType* signalId) {
    for (uint32 i = 0; i < PORT_MAPPING_COUNT; i++) {
        if (port_mapping[i].componentId == componentId && 
            port_mapping[i].portId == portId) {
            *signalId = port_mapping[i].signalId;
            return E_OK;
        }
    }
    return E_NOT_OK;
}

Std_ReturnType Rte_Init(void) {
    printf("[RTE] Initializing Runtime Environment...\n");
    printf("[RTE] Port mappings configured: %u\n", PORT_MAPPING_COUNT);
    return E_OK;
}

Std_ReturnType Rte_Start(void) {
    printf("[RTE] Starting RTE...\n");
    /* SWC runnables are registered with OS and will be called automatically */
    return E_OK;
}

Std_ReturnType Rte_Read(uint8 componentId, uint8 portId, void* data) {
    Com_SignalIdType signalId;
    
    if (data == NULL) {
        return E_NOT_OK;
    }
    
    if (Rte_FindSignal(componentId, portId, FALSE, &signalId) != E_OK) {
        return E_NOT_OK;
    }
    
    return Com_ReceiveSignal(signalId, (uint32*)data);
}

Std_ReturnType Rte_Write(uint8 componentId, uint8 portId, const void* data) {
    Com_SignalIdType signalId;
    
    if (data == NULL) {
        return E_NOT_OK;
    }
    
    if (Rte_FindSignal(componentId, portId, TRUE, &signalId) != E_OK) {
        return E_NOT_OK;
    }
    
    return Com_SendSignal(signalId, *(const uint32*)data);
}
