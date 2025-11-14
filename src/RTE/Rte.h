#ifndef RTE_H
#define RTE_H

/*===========================================================================*/
/**
 * @file Rte.h
 *
 *  The API for the RTE
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * @todo Add full description here
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - @todo Update list of other applicable standards
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include <stdint.h>

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */
/*===========================================================================*
 * Exported Preprocessor #define Constants
 *===========================================================================*/
#define RTE_E_OK 0

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/
typedef int Std_ReturnType;

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/
Std_ReturnType Rte_Write_VehicleSpeed(uint16_t value);
Std_ReturnType Rte_Read_VehicleSpeed(uint16_t *value);

uint8_t  Rte_Call_NvM_ReadBlock(uint16_t blockId);
void     Rte_Call_NvM_WriteBlock(uint16_t blockId, uint8_t value);

#   ifdef __cplusplus
}         /* extern "C" */
#   endif /* __cplusplus */
/*===========================================================================*/
/*===========================================================================*/
#endif /* RTE_H */
