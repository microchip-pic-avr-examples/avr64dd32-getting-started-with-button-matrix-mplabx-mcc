/**
 * \file button_matrix.c
 *
 * \brief Button Matrix Event Handler functionalities file.
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

#include "button_matrix.h"

static int pressed_buttons = 0;
static bool multiple_event_f = 0;
static bool long_event_f = 0;
static bool double_event_f = 0;
static uint8_t buttons[] = {BM_NULL_BTN, BM_NULL_BTN, BM_NULL_BTN};

bmEvent_cb_t bmEventHandler_TransferEvent_Cb;

/* Function that sets the transfer event callback */
void BUTTON_MATRIX_setEventCallback(bmEvent_cb_t function)
{
    bmEventHandler_TransferEvent_Cb = function;
}

/* Callback for TCB0 - will transmit the long button press event */
void bmEventHandler_timer_Cb(void)
{
    if(NULL != bmEventHandler_TransferEvent_Cb)
    {
        if(!multiple_event_f && !double_event_f)
        {
            bmEventHandler_TransferEvent_Cb(LONG_PRESS, buttons[0], BM_NULL_BTN);
        }
        else if (double_event_f)
        {
            bmEventHandler_TransferEvent_Cb(MULTIPLE_LONG_PRESS, buttons[0], buttons[1]);
        }
    }
    
    long_event_f = 1;
}

/* Function that receives the state of a button and transmits the event */
void BUTTON_MATRIX_EventHandler(uint8_t button, bool state)
{
    if(state == BM_BUTTON_PRESSED)
    {
        switch(pressed_buttons)
        {
            case 0:
                RTC_Start();
                buttons[pressed_buttons] = button;
                pressed_buttons++;
                multiple_event_f = 0;
                double_event_f = 0;
                long_event_f = 0;
                break;
            case 1:
                RTC_Start();
                buttons[pressed_buttons] = button;
                pressed_buttons++;
                multiple_event_f = 0;
                double_event_f = 1;
                long_event_f = 0;
                break;
            case 2:
                RTC_Stop();
                if(NULL != bmEventHandler_TransferEvent_Cb)
                {
                    bmEventHandler_TransferEvent_Cb(ERROR, BM_NULL_BTN, BM_NULL_BTN);
                }
                buttons[pressed_buttons] = button;
                pressed_buttons++;
                multiple_event_f = 1;
                double_event_f = 0;
                long_event_f = 0;
                break;
            default:
                multiple_event_f = 1;
                break;
        }
    }
    else if(state == BM_BUTTON_RELEASED)
    {
        RTC_Stop();
        if((!long_event_f) && (!multiple_event_f))
        {
            if(NULL != bmEventHandler_TransferEvent_Cb)
            {
                if(double_event_f)
                {
                    multiple_event_f = 1;
                    bmEventHandler_TransferEvent_Cb(MULTIPLE_SHORT_PRESS, buttons[0], buttons[1]);
                }
                else
                    bmEventHandler_TransferEvent_Cb(SHORT_PRESS, buttons[pressed_buttons - 1], BM_NULL_BTN);
            }
        }
        
        for(int i = 0; i < pressed_buttons; i++)
        {
            if(buttons[i] == button)
            {
                for(int j = i; j < pressed_buttons - 1; j++)
                {
                    buttons[j] = buttons[j + 1];
                }
                buttons[pressed_buttons - 1] = BM_NULL_BTN;
                pressed_buttons--;
            }
        }
    }
    
}

/* Function that initializes the buttons array, and sets necessary ISR callback functions */
void BUTTON_MATRIX_init(void)
{
    pressed_buttons = 0;
    multiple_event_f = 0;
    long_event_f = 0;
    double_event_f = 0;
    buttons[0] = BM_NULL_BTN;
    buttons[1] = BM_NULL_BTN;
    buttons[2] = BM_NULL_BTN;
    
    RTC_SetOVFIsrCallback(bmEventHandler_timer_Cb);
    buttonMatrixPhy_init();
}