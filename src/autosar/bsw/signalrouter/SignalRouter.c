/**
 * @file SignalRouter.c
 * @brief Internal Signal Router - Implementation
 * @details Manages in-memory signal exchange between SWCs
 * 
 * Location: src/autosar/bsw/signalrouter/SignalRouter.c
 */

#include "SignalRouter.h"
#include <stdio.h>
#include <string.h>

/* Internal signal database (private to this module) */
static SignalRouter_SignalDataType signal_db[SIGNAL_COUNT];

Std_ReturnType SignalRouter_Init(void) {
    /* Initialize all signals to zero */
    memset(signal_db, 0, sizeof(signal_db));
    
    printf("[SignalRouter] Initialized - %u internal signals\n", SIGNAL_COUNT);
    printf("[SignalRouter] Note: This handles INTERNAL routing, not bus communication\n");
    
    return E_OK;
}

Std_ReturnType SignalRouter_Write(SignalRouter_SignalIdType signalId, uint32 value) {
    /* Validate signal ID */
    if (signalId >= SIGNAL_COUNT) {
        printf("[SignalRouter] ERROR: Invalid signal ID %u\n", signalId);
        return E_NOT_OK;
    }
    
    /* Write value and mark as updated */
    signal_db[signalId].value = value;
    signal_db[signalId].updated = TRUE;
    
    return E_OK;
}

Std_ReturnType SignalRouter_Read(SignalRouter_SignalIdType signalId, uint32* value) {
    /* Validate inputs */
    if (signalId >= SIGNAL_COUNT) {
        printf("[SignalRouter] ERROR: Invalid signal ID %u\n", signalId);
        return E_NOT_OK;
    }
    
    if (value == NULL) {
        printf("[SignalRouter] ERROR: NULL pointer provided\n");
        return E_NOT_OK;
    }
    
    /* Read value and clear update flag */
    *value = signal_db[signalId].value;
    signal_db[signalId].updated = FALSE;
    
    return E_OK;
}

boolean SignalRouter_IsUpdated(SignalRouter_SignalIdType signalId) {
    /* Validate signal ID */
    if (signalId >= SIGNAL_COUNT) {
        return FALSE;
    }
    
    return signal_db[signalId].updated;
}
