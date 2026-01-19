/**
 * @file SignalRouter.h
 * @brief Internal Signal Router - Header
 * @details In-memory signal routing for inter-SWC communication within the ECU
 * 
 * Location: src/autosar/bsw/signalrouter/SignalRouter.h
 * 
 * ============================================================================
 * IMPORTANT CLARIFICATION:
 * ============================================================================
 * This is NOT the AUTOSAR COM module!
 * 
 * In real AUTOSAR:
 * - COM module handles BUS communication (CAN, LIN, FlexRay, Ethernet)
 * - COM packs/unpacks signals into PDUs (Protocol Data Units)
 * - COM manages transmission and reception on physical buses
 * 
 * This module:
 * - Handles INTERNAL signal routing between SWCs within the same ECU
 * - Provides in-memory data exchange (no bus involved)
 * - Used by RTE for inter-component communication
 * - Think of it as a "shared memory manager" for signals
 * 
 * In a complete AUTOSAR system:
 *   SWC → RTE → SignalRouter (internal) → RTE → SWC  [Same ECU]
 *   SWC → RTE → COM → CAN/LIN → COM → RTE → SWC      [Different ECUs]
 * ============================================================================
 */

#ifndef SIGNAL_ROUTER_H
#define SIGNAL_ROUTER_H

#include "Std_Types.h"

/* Signal IDs for internal routing */
typedef enum {
    SIGNAL_INPUT_A = 0,
    SIGNAL_INPUT_B,
    SIGNAL_OUTPUT_RESULT,
    SIGNAL_STATUS,
    SIGNAL_COUNT
} SignalRouter_SignalIdType;

/* Signal data buffer structure */
typedef struct {
    uint32 value;
    boolean updated;
} SignalRouter_SignalDataType;

/**
 * @brief Initialize the Signal Router
 * @return E_OK if successful
 */
Std_ReturnType SignalRouter_Init(void);

/**
 * @brief Write a signal value to internal buffer
 * @param signalId Signal identifier
 * @param value Value to write
 * @return E_OK if successful, E_NOT_OK if signal ID invalid
 */
Std_ReturnType SignalRouter_Write(SignalRouter_SignalIdType signalId, uint32 value);

/**
 * @brief Read a signal value from internal buffer
 * @param signalId Signal identifier
 * @param value Pointer to store read value
 * @return E_OK if successful, E_NOT_OK if signal ID invalid or pointer NULL
 */
Std_ReturnType SignalRouter_Read(SignalRouter_SignalIdType signalId, uint32* value);

/**
 * @brief Check if a signal has been updated since last read
 * @param signalId Signal identifier
 * @return TRUE if updated, FALSE otherwise
 */
boolean SignalRouter_IsUpdated(SignalRouter_SignalIdType signalId);

#endif /* SIGNAL_ROUTER_H */
