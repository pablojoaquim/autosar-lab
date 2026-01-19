/**
 * @file Com.h
 * @brief AUTOSAR COM Module - Header (Educational/Simulated)
 * @details Simulates bus communication (CAN, LIN, FlexRay, Ethernet)
 * 
 * Location: src/autosar/bsw/com/Com.h
 * 
 * ============================================================================
 * THIS IS THE REAL AUTOSAR COM MODULE
 * ============================================================================
 * 
 * Purpose: Handle communication over physical buses
 * 
 * Responsibilities:
 * - Pack signals into PDUs (Protocol Data Units / frames)
 * - Unpack PDUs into signals
 * - Manage transmission timing (periodic, event-triggered)
 * - Handle reception (timeout monitoring, notification)
 * - Gateway routing between different buses
 * 
 * Example flow:
 *   Application ? RTE ? COM ? CanIf ? Can Driver ? Physical CAN Bus
 * 
 * This is a SIMULATED version for learning:
 * - No real hardware access
 * - Prints "bus frames" to console
 * - Demonstrates COM concepts without hardware
 * ============================================================================
 */

#ifndef COM_H
#define COM_H

#include "Std_Types.h"

/* COM Signal IDs (signals that go over the bus) */
typedef enum {
    COM_SIGNAL_ENGINE_SPEED = 0,     /* RPM - sent on CAN */
    COM_SIGNAL_VEHICLE_SPEED,        /* km/h - sent on CAN */
    COM_SIGNAL_DOOR_STATUS,          /* Bitmap - sent on LIN */
    COM_SIGNAL_DIAGNOSTICS,          /* Status - sent on CAN */
    COM_SIGNAL_BUS_COUNT
} Com_SignalIdType;

/* I-PDU IDs (CAN frames, LIN frames, etc.) */
typedef enum {
    COM_IPDU_ENGINE_DATA = 0,        /* CAN frame 0x100 */
    COM_IPDU_VEHICLE_DATA,           /* CAN frame 0x200 */
    COM_IPDU_BODY_DATA,              /* LIN frame 0x01 */
    COM_IPDU_DIAG_DATA,              /* CAN frame 0x7DF */
    COM_IPDU_COUNT
} Com_PduIdType;

/* Bus types */
typedef enum {
    COM_BUS_CAN = 0,
    COM_BUS_LIN,
    COM_BUS_FLEXRAY,
    COM_BUS_ETH
} Com_BusType;

/* Transmission mode */
typedef enum {
    COM_TX_MODE_PERIODIC = 0,        /* Sent every N ms */
    COM_TX_MODE_DIRECT,              /* Sent immediately */
    COM_TX_MODE_MIXED                /* Periodic + on change */
} Com_TxModeType;

/**
 * @brief Initialize the COM module
 * @return E_OK if successful
 */
Std_ReturnType Com_Init(void);

/**
 * @brief Send a signal over the bus
 * @details Packs signal into appropriate PDU and schedules transmission
 * @param signalId Signal identifier
 * @param signalData Pointer to signal data
 * @return E_OK if successful
 */
Std_ReturnType Com_SendSignal(Com_SignalIdType signalId, const void* signalData);

/**
 * @brief Receive a signal from the bus
 * @details Unpacks signal from received PDU
 * @param signalId Signal identifier
 * @param signalData Pointer to store received data
 * @return E_OK if successful
 */
Std_ReturnType Com_ReceiveSignal(Com_SignalIdType signalId, void* signalData);

/**
 * @brief Main transmission function
 * @details Called periodically to handle transmission scheduling
 * Should be called from a periodic OS task (typically 5-10ms)
 */
void Com_MainFunctionTx(void);

/**
 * @brief Main reception function
 * @details Called periodically to handle timeout monitoring
 * Should be called from a periodic OS task (typically 5-10ms)
 */
void Com_MainFunctionRx(void);

/**
 * @brief Transmission confirmation callback
 * @details Called by lower layer when PDU transmission is confirmed
 * @param pduId PDU that was transmitted
 */
void Com_TxConfirmation(Com_PduIdType pduId);

/**
 * @brief Reception indication callback
 * @details Called by lower layer when PDU is received
 * @param pduId PDU that was received
 * @param pduData Pointer to received data
 * @param pduLength Length of received data
 */
void Com_RxIndication(Com_PduIdType pduId, const uint8* pduData, uint8 pduLength);

#endif /* COM_H */
