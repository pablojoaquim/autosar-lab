/*===========================================================================*/
/**
 * @file SpeedSensor.c
 *
 *  A SWC that emulates the reading of a speed sensor value
 *
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * @todo Divide this file content using an abstraction layers concept
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
#include "Rte.h"
#include <stdint.h>
#include <stdio.h>

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Local Variables Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

/***************************************************************************//**
* @fn         SpeedSensor_Runnable
* @brief      Read the speed from the sensor and send the value to the RTE
* @param [in] void
* @return     void
******************************************************************************/
void SpeedSensor_Runnable(void)
{
    static uint16_t speed = 0;
    speed = (speed + 5) % 200;   // sensor simulation
    Rte_Write_VehicleSpeed(speed);

    if (speed > 100)
    {
        Rte_Call_NvM_WriteBlock(1, speed);
        printf("[SpeedSensor] New speed stored: %u\n", speed);
    }    
}
