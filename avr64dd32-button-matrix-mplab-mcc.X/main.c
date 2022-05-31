/*
    (c) 2021 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <util/atomic.h>
#include "mcc_generated_files/system/system.h"
#include "button_matrix.h"

static volatile BUTTON_MATRIX_event_t event = NONE;
static volatile uint8_t btn1 = BM_NULL_BTN; 
static volatile uint8_t btn2 = BM_NULL_BTN;

/*
 * Event transfer callback
 * This function is used to transfer the event (and the buttons information) 
 * when an event occurs.
 */

void MyKeyboardCallback(BUTTON_MATRIX_event_t bm_event, uint8_t bm_btn1, uint8_t bm_btn2)
{
    event = bm_event;
    btn1 = bm_btn1;
    btn2 = bm_btn2;
}

/*
    Main application
*/

int main(void)
{
    BUTTON_MATRIX_event_t temp_event = NONE;
    uint8_t temp_btn1 = BM_NULL_BTN; 
    uint8_t temp_btn2 = BM_NULL_BTN;
    
    SYSTEM_Initialize();
    BUTTON_MATRIX_setEventCallback(MyKeyboardCallback);
    BUTTON_MATRIX_init();
    
    
    while(1)
    {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            if(event != NONE)
            {
                temp_event = event;
                temp_btn1 = btn1; 
                temp_btn2 = btn2;
                
                event = NONE;
                btn1 = BM_NULL_BTN; 
                btn2 = BM_NULL_BTN;
            }
        }
        switch(temp_event)
        {
            case ERROR:
                printf("Too many buttons are pressed at once!\n\r");
                break;
            case LONG_PRESS:
                printf("S%d was pressed for a long time!\n\r", temp_btn1);
                break;
            case MULTIPLE_SHORT_PRESS:
                printf("S%d and S%d were pressed for a short time!\n\r", temp_btn1, temp_btn2);
                break;
            case MULTIPLE_LONG_PRESS:
                printf("S%d and S%d were pressed for a long time!\n\r", temp_btn1, temp_btn2);
                break;
            case SHORT_PRESS:
                printf("S%d was pressed for a short time!\n\r", temp_btn1);
                break;
            default:
                break;
        }
        
        temp_event = NONE;
        temp_btn1 = BM_NULL_BTN; 
        temp_btn2 = BM_NULL_BTN;
    }
}

/**
    End of File
*/