/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

#ifndef CONFIG_H
#define	CONFIG_H   

#define CFG_COLUMNS              4
#define CFG_ROWS                 4
#define CFG_DEBOUNCE_TIME        4    /* 4 * 20 ms */

/*
 * Pin Mapping (in order):
 * | Button Matrix | PORT Pin |
 * -------------------------------
 * |      1        |   PA3    | C3
 * |      2        |   PA2    | C2
 * |      3        |   PC1    | C1
 * |      4        |   PC0    | C0
 * |      5        |   PA4    | L0
 * |      6        |   PA5    | L1
 * |      7        |   PA6    | L2
 * |      8        |   PA7    | L3
 */

#define CFG_COLUMN0_PORT         PORTC
#define CFG_COLUMN0_PIN          0
#define CFG_COLUMN1_PORT         PORTC
#define CFG_COLUMN1_PIN          1
#define CFG_COLUMN2_PORT         PORTA
#define CFG_COLUMN2_PIN          2
#define CFG_COLUMN3_PORT         PORTA
#define CFG_COLUMN3_PIN          3
#define CFG_ROW0_PORT            PORTA
#define CFG_ROW0_PIN             4
#define CFG_ROW1_PORT            PORTA
#define CFG_ROW1_PIN             5
#define CFG_ROW2_PORT            PORTA
#define CFG_ROW2_PIN             6
#define CFG_ROW3_PORT            PORTA
#define CFG_ROW3_PIN             7    

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* CONFIG_H */
