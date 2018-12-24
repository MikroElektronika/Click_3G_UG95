/*
    __c3g_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __c3g_driver.h
@brief    3G Driver
@mainpage 3G Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   C3G
@brief      3G Click Driver
@{

| Global Library Prefix | **C3G** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jan 2018.**      |
| Developer             | **MikroE Team**     |

Command parser core configured for AT command based GSM devices.

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"
#include "stdbool.h"

#ifndef _C3G_H_
#define _C3G_H_

/**
 * @macro T_C3G_P 
 * @brief Global Abstract Macro 
 */
#define T_C3G_P    const uint8_t*

/** @defgroup C3G_AT_CMDS AT Command Types */                /** @{ */

extern const uint8_t _C3G_UNKNOWN ;                                   /**< Unknown command type */
extern const uint8_t _C3G_TEST    ;                                   /**< Test command type */
extern const uint8_t _C3G_SET     ;                                   /**< Set command type */
extern const uint8_t _C3G_GET     ;                                   /**< Get command type */
extern const uint8_t _C3G_URC     ;                                   /**< URC */
extern const uint8_t _C3G_EXEC    ;                                   /**< Exec command type */
                                                                       /** @} */
/** @defgroup C3G_AT_EVARG 3G Event Arguments */   /** @{ */

extern const uint8_t _C3G_EVARG_START_T    ;                          /**< Event argument 0 */
extern const uint8_t _C3G_EVARG_END_T      ;                          /**< Event argument 1 */
extern const uint8_t _C3G_EVARG_EVENT_T    ;                          /**< Event argument 2 */
                          
extern const uint8_t _C3G_EVENT_RESPONSE   ;                          /**< Response */
extern const uint8_t _C3G_EVENT_TIMEOUT    ;                          /**< Timeout */
extern const uint8_t _C3G_EVENT_BUFFER_OUT ;                          /**< Buffer warning */
extern const uint8_t _C3G_EVENT_CALLBACK   ;                          /** Callback */
                                                                       /** @} */
/**
 * @typedef T_c3g_handler
 * @brief Handler Prototype
 */
typedef void ( *T_c3g_handler )( char *buffer, uint8_t *evArgs );

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup C3G_INIT Driver Init Functions */              /** @{ */

/**
 * @brief Driver Initialization
 * 
 * @param[in] gpioObj pointer to GPIO object
 * @param[in] uartObj pointer to UART object
 *
 * Default UART driver intializaton function.
 */
void c3g_uartDriverInit(T_C3G_P gpioObj, T_C3G_P uartObj);

/**
 * @brief Core Initialization
 *
 * @param[in] defaultHdl        default handler
 * @param[in] defaultWdog       default watchdog
 *
 * Initialization should be executed before any other function. User can
 * execute this function later inside the application to reset AT Engine to
 * the default state.
 */
void c3g_coreInit( T_c3g_handler defaultHdl, uint32_t defaultWdog );

                                                                       /** @} */
/** @defgroup C3G_FUNC Driver Functions */                   /** @{ */

/** 
 * @brief Hardware Flow Control State
 *
 * @param[in] hfcState 
 *
 * Enables or disables Hardware Flow Control.
 */
void c3g_hfcEnable( bool hfcState );

/**
 * @brief Enables or disables module power
 *
 * @param[in] powerState
 *
 * Turn ON or OFF the module.
 */
void c3g_modulePower( bool powerState );

/**
 * @brief Receive
 *
 * @param[in] rxInput       char received from the module
 *
 * Function is used to populate response buffer with characters received from
 * the module. This function should be placed inside UART ISR function.It also
 * can be used inside function which constatnly poll the UART RX register.
 */
void c3g_putc( char rxInput );

/**
 * @brief Engine Tick
 *
 * Function must be placed inside the Timer ISR function which will be called
 * every one millisecond.
 */
void c3g_tick();

/**
 * @brief Save AT Command to Storage
 *
 * @param[in] pCmd          command string
 * @param[in] timeout       timeout for provided command
 * @param[in] pHandler      handler for provided command
 *
 * Saves handlers and timeout for the particular command.
 */
uint16_t c3g_setHandler( char *pCmd, uint32_t timeout, T_c3g_handler pHandler );

/**
 * @brief Simple AT Command
 *
 * @param[in] pCmd          pointer to command string
 *
 * Function should be used in case of simple AT commands which have no
 * additional arguments expected. Most of the AT Commands uses this function.
 */
void c3g_cmdSingle( char *pCmd );

/**
 * @brief Doble AT Command
 *
 * @param[in] pCmd          pointer to command string
 * @param[in] pArg1         pointer to the string used as additional argument
 *
 * Function should be used with AT commands which expects additional data after
 * the module responses with specific character. In most cases special character
 * is ">" like in example of AT command for SMS sending.
 */
void c3g_cmdDouble( char *pCmd, char *pArg1 );

/**
 * @brief Triple AT Command
 *
 * @param[in] pCmd          pointer to command string
 * @param[in] pArg1         pointer to the string used as additional argument
 * @param[in] pArg2         pointer to the second additional argument
 *
 * Function should be used with AT command which excepts two additional
 * parameters after the execution of the command. This kind of AT functions are
 * very rare.
 */
void c3g_cmdTriple( char *pCmd, char *pArg1, char *pArg2 );

/**
 * @brief AT Engine State Machine
 *
 * This function should be placed inside the infinite while loop.
 */
void c3g_process();
                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_3G_STM.c
    @example Click_3G_TIVA.c
    @example Click_3G_CEC.c
    @example Click_3G_KINETIS.c
    @example Click_3G_MSP.c
    @example Click_3G_PIC.c
    @example Click_3G_PIC32.c
    @example Click_3G_DSPIC.c
    @example Click_3G_AVR.c
    @example Click_3G_FT90x.c
    @example Click_3G_STM.mbas
    @example Click_3G_TIVA.mbas
    @example Click_3G_CEC.mbas
    @example Click_3G_KINETIS.mbas
    @example Click_3G_MSP.mbas
    @example Click_3G_PIC.mbas
    @example Click_3G_PIC32.mbas
    @example Click_3G_DSPIC.mbas
    @example Click_3G_AVR.mbas
    @example Click_3G_FT90x.mbas
    @example Click_3G_STM.mpas
    @example Click_3G_TIVA.mpas
    @example Click_3G_CEC.mpas
    @example Click_3G_KINETIS.mpas
    @example Click_3G_MSP.mpas
    @example Click_3G_PIC.mpas
    @example Click_3G_PIC32.mpas
    @example Click_3G_DSPIC.mpas
    @example Click_3G_AVR.mpas
    @example Click_3G_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __c3g_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */
