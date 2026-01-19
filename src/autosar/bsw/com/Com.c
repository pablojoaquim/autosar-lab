/**
 * @file Com.c
 * @brief AUTOSAR COM Module - Implementation (Educational/Simulated)
 * @details Simulates bus communication behavior
 * 
 * Location: src/autosar/bsw/com/Com.c
 */

#include "Com.h"
#include <stdio.h>
#include <string.h>

/* PDU buffer structure (simulates CAN/LIN frame) */
typedef struct {
    uint8 data[8];           /* PDU data (max 8 bytes for CAN) */
    uint8 length;            /* Actual data length */
    Com_BusType busType;     /* Which bus this PDU uses */
    uint32 canId;            /* CAN ID (if CAN bus) */
    boolean pending;         /* Transmission pending flag */
} Com_PduBufferType;

/* Signal to PDU mapping */
typedef struct {
    Com_SignalIdType signalId;
    Com_PduIdType pduId;
    uint8 startBit;          /* Bit position in PDU */
    uint8 bitLength;         /* Signal length in bits */
} Com_SignalMappingType;

/* PDU transmission buffers */
static Com_PduBufferType tx_buffers[COM_IPDU_COUNT];
static Com_PduBufferType rx_buffers[COM_IPDU_COUNT];

/* Signal values cache */
static uint32 tx_signals[COM_SIGNAL_BUS_COUNT];
static uint32 rx_signals[COM_SIGNAL_BUS_COUNT];

/* Signal to PDU mapping table */
static const Com_SignalMappingType signal_mapping[] = {
    /* signalId,              pduId,                startBit, bitLength */
    {COM_SIGNAL_ENGINE_SPEED,  COM_IPDU_ENGINE_DATA,  0,       16},  /* Bytes 0-1 */
    {COM_SIGNAL_VEHICLE_SPEED, COM_IPDU_VEHICLE_DATA, 0,       16},  /* Bytes 0-1 */
    {COM_SIGNAL_DOOR_STATUS,   COM_IPDU_BODY_DATA,    0,       8},   /* Byte 0 */
    {COM_SIGNAL_DIAGNOSTICS,   COM_IPDU_DIAG_DATA,    0,       32},  /* Bytes 0-3 */
};

/* PDU configuration */
static const struct {
    Com_PduIdType pduId;
    Com_BusType busType;
    uint32 canId;
    uint16 txPeriod;         /* Transmission period in ms */
    Com_TxModeType txMode;
} pdu_config[] = {
    {COM_IPDU_ENGINE_DATA,  COM_BUS_CAN, 0x100, 10,  COM_TX_MODE_PERIODIC},
    {COM_IPDU_VEHICLE_DATA, COM_BUS_CAN, 0x200, 20,  COM_TX_MODE_PERIODIC},
    {COM_IPDU_BODY_DATA,    COM_BUS_LIN, 0x01,  100, COM_TX_MODE_PERIODIC},
    {COM_IPDU_DIAG_DATA,    COM_BUS_CAN, 0x7DF, 0,   COM_TX_MODE_DIRECT},
};

/* Helper: Pack signal into PDU buffer */
static void PackSignalIntoPdu(Com_SignalIdType signalId, uint32 value) {
    for (uint32 i = 0; i < sizeof(signal_mapping) / sizeof(signal_mapping[0]); i++) {
        if (signal_mapping[i].signalId == signalId) {
            Com_PduIdType pduId = signal_mapping[i].pduId;
            uint8 startBit = signal_mapping[i].startBit;
            uint8 bitLength = signal_mapping[i].bitLength;
            
            /* Simple byte-aligned packing for demonstration */
            uint8 startByte = startBit / 8;
            
            if (bitLength == 8) {
                tx_buffers[pduId].data[startByte] = (uint8)value;
            } else if (bitLength == 16) {
                tx_buffers[pduId].data[startByte] = (uint8)(value & 0xFF);
                tx_buffers[pduId].data[startByte + 1] = (uint8)((value >> 8) & 0xFF);
            } else if (bitLength == 32) {
                tx_buffers[pduId].data[startByte] = (uint8)(value & 0xFF);
                tx_buffers[pduId].data[startByte + 1] = (uint8)((value >> 8) & 0xFF);
                tx_buffers[pduId].data[startByte + 2] = (uint8)((value >> 16) & 0xFF);
                tx_buffers[pduId].data[startByte + 3] = (uint8)((value >> 24) & 0xFF);
            }
            
            tx_buffers[pduId].pending = TRUE;
            break;
        }
    }
}

/* Helper: Unpack signal from PDU buffer */
static uint32 UnpackSignalFromPdu(Com_SignalIdType signalId) {
    uint32 value = 0;
    
    for (uint32 i = 0; i < sizeof(signal_mapping) / sizeof(signal_mapping[0]); i++) {
        if (signal_mapping[i].signalId == signalId) {
            Com_PduIdType pduId = signal_mapping[i].pduId;
            uint8 startBit = signal_mapping[i].startBit;
            uint8 bitLength = signal_mapping[i].bitLength;
            
            /* Simple byte-aligned unpacking */
            uint8 startByte = startBit / 8;
            
            if (bitLength == 8) {
                value = rx_buffers[pduId].data[startByte];
            } else if (bitLength == 16) {
                value = rx_buffers[pduId].data[startByte] |
                       (rx_buffers[pduId].data[startByte + 1] << 8);
            } else if (bitLength == 32) {
                value = rx_buffers[pduId].data[startByte] |
                       (rx_buffers[pduId].data[startByte + 1] << 8) |
                       (rx_buffers[pduId].data[startByte + 2] << 16) |
                       (rx_buffers[pduId].data[startByte + 3] << 24);
            }
            break;
        }
    }
    
    return value;
}

Std_ReturnType Com_Init(void) {
    /* Initialize PDU buffers */
    memset(tx_buffers, 0, sizeof(tx_buffers));
    memset(rx_buffers, 0, sizeof(rx_buffers));
    
    /* Initialize signal caches */
    memset(tx_signals, 0, sizeof(tx_signals));
    memset(rx_signals, 0, sizeof(rx_signals));
    
    /* Configure PDU properties */
    for (uint32 i = 0; i < sizeof(pdu_config) / sizeof(pdu_config[0]); i++) {
        Com_PduIdType pduId = pdu_config[i].pduId;
        tx_buffers[pduId].busType = pdu_config[i].busType;
        tx_buffers[pduId].canId = pdu_config[i].canId;
        tx_buffers[pduId].length = 8;  /* Default to 8 bytes */
    }
    
    printf("[COM] Initialized - REAL AUTOSAR COM for bus communication\n");
    printf("[COM] Configured %lu PDUs for transmission\n", 
           sizeof(pdu_config) / sizeof(pdu_config[0]));
    printf("[COM] Supports: CAN, LIN (simulated)\n");
    
    return E_OK;
}

Std_ReturnType Com_SendSignal(Com_SignalIdType signalId, const void* signalData) {
    if (signalId >= COM_SIGNAL_BUS_COUNT || signalData == NULL) {
        return E_NOT_OK;
    }
    
    /* Cache the signal value */
    uint32 value = *(const uint32*)signalData;
    tx_signals[signalId] = value;
    
    /* Pack signal into PDU */
    PackSignalIntoPdu(signalId, value);
    
    printf("[COM] Signal %u prepared for transmission (value: %u)\n", signalId, value);
    
    return E_OK;
}

Std_ReturnType Com_ReceiveSignal(Com_SignalIdType signalId, void* signalData) {
    if (signalId >= COM_SIGNAL_BUS_COUNT || signalData == NULL) {
        return E_NOT_OK;
    }
    
    /* Return cached signal value */
    *(uint32*)signalData = rx_signals[signalId];
    
    return E_OK;
}

void Com_MainFunctionTx(void) {
    /* Simulate periodic transmission */
    static uint32 cycle_counter = 0;
    cycle_counter++;
    
    /* Check each PDU for transmission */
    for (uint32 i = 0; i < COM_IPDU_COUNT; i++) {
        if (tx_buffers[i].pending) {
            /* Simulate bus transmission */
            const char* bus_name = (tx_buffers[i].busType == COM_BUS_CAN) ? "CAN" : "LIN";
            
            printf("[COM] TX %s ID 0x%03X: [", bus_name, tx_buffers[i].canId);
            for (uint8 j = 0; j < 8; j++) {
                printf("%02X ", tx_buffers[i].data[j]);
            }
            printf("]\n");
            
            /* Clear pending flag */
            tx_buffers[i].pending = FALSE;
            
            /* Simulate transmission confirmation */
            Com_TxConfirmation(i);
        }
    }
}

void Com_MainFunctionRx(void) {
    /* In real AUTOSAR, this would:
     * - Check for timeout on expected messages
     * - Handle deadline monitoring
     * - Process reception notifications
     */
    
    /* For simulation, we could auto-loop transmitted data back as received */
    /* (This simulates a loopback mode or another ECU responding) */
}

void Com_TxConfirmation(Com_PduIdType pduId) {
    if (pduId >= COM_IPDU_COUNT) {
        return;
    }
    
    printf("[COM] TX Confirmation for PDU %u\n", pduId);
    
    /* In real AUTOSAR:
     * - Notify upper layers
     * - Update transmission counters
     * - Trigger transmission notifications
     */
}

void Com_RxIndication(Com_PduIdType pduId, const uint8* pduData, uint8 pduLength) {
    if (pduId >= COM_IPDU_COUNT || pduData == NULL) {
        return;
    }
    
    printf("[COM] RX Indication PDU %u: [", pduId);
    for (uint8 i = 0; i < pduLength; i++) {
        printf("%02X ", pduData[i]);
    }
    printf("]\n");
    
    /* Copy to reception buffer */
    memcpy(rx_buffers[pduId].data, pduData, pduLength);
    rx_buffers[pduId].length = pduLength;
    
    /* Unpack signals from PDU */
    for (uint32 i = 0; i < sizeof(signal_mapping) / sizeof(signal_mapping[0]); i++) {
        if (signal_mapping[i].pduId == pduId) {
            uint32 value = UnpackSignalFromPdu(signal_mapping[i].signalId);
            rx_signals[signal_mapping[i].signalId] = value;
            printf("[COM] Unpacked signal %u = %u\n", signal_mapping[i].signalId, value);
        }
    }
    
    /* In real AUTOSAR:
     * - Validate DLC (Data Length Code)
     * - Check signal ranges
     * - Trigger reception notifications
     * - Update timeout counters
     */
}
