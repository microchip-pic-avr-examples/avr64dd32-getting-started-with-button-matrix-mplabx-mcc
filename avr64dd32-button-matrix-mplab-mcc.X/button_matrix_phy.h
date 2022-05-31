/**
 * \file button_matrix.h
 *
 * \brief Button Matrix specific macro definitions and public functions headers.
 *
 (c) 2021 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#ifndef BUTTON_MATRIX
#define	BUTTON_MATRIX

#include "mcc_generated_files/system/system.h"
#include "button_matrix_config.h"
#include "button_matrix.h"
#include <util/delay.h>

/* Offset needed to enable the pull-up on a specific pin */
#define BM_PORT_OFFSET          (&(PORTA.PIN0CTRL) - &(PORTA.DIR))
/* Default value used to indicate that none of the buttons have been pressed */
#define BM_NULL_BTN             0
    
#define BM_BUTTON_PRESSED       0
#define BM_BUTTON_RELEASED      1

typedef struct {
    PORT_t *port;
    uint8_t position;
} pin_t;

typedef struct {
    uint8_t debounce_count;
    bool state;
} button_t;

void buttonMatrixPhy_init(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BUTTON_MATRIX */
