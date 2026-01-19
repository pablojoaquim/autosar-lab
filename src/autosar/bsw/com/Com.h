/**
 * @file Com.h
 * @brief AUTOSAR Communication Module - Header
 * @details Signal routing and data management
 * 
 * Location: src/autosar/bsw/com/Com.h
 */

#ifndef COM_H
#define COM_H

#include "Std_Types.h"

/* Signal IDs */
typedef enum {
    COM_SIGNAL_INPUT_A = 0,
    COM_SIGNAL_INPUT_B,
    COM_SIGNAL_OUTPUT_RESULT,
    COM_SIGNAL_STATUS,
    COM_SIGNAL_COUNT
} Com_SignalIdType;

/* Signal data buffer */
typedef struct {
    uint32 value;
    boolean updated;
} Com_SignalDataType;

/**
 * @brief Initialize the COM module
 * @return E_OK if successful
 */
Std_ReturnType Com_Init(void);

/**
 * @brief Write a signal value
 * @param signalId Signal identifier
 * @param value Value to write
 * @return E_OK if successful
 */
Std_ReturnType Com_SendSignal(Com_SignalIdType signalId, uint32 value);

/**
 * @brief Read a signal value
 * @param signalId Signal identifier
 * @param value Pointer to store read value
 * @return E_OK if successful
 */
Std_ReturnType Com_ReceiveSignal(Com_SignalIdType signalId, uint32* value);

/**
 * @brief Main function - called periodically
 */
void Com_MainFunction(void);

#endif /* COM_H */
