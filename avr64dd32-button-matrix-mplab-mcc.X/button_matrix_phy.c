/**
 * \file button_matrix.c
 *
 * \brief Button Matrix low level functionalities file.
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

#include "button_matrix_phy.h"

static const pin_t columns[CFG_COLUMNS] = {
    {.port = &CFG_COLUMN0_PORT, .position = CFG_COLUMN0_PIN},
    {.port = &CFG_COLUMN1_PORT, .position = CFG_COLUMN1_PIN},
    {.port = &CFG_COLUMN2_PORT, .position = CFG_COLUMN2_PIN},
    {.port = &CFG_COLUMN3_PORT, .position = CFG_COLUMN3_PIN}
};

static const pin_t rows[CFG_ROWS] = {
    {.port = &CFG_ROW0_PORT, .position = CFG_ROW0_PIN},
    {.port = &CFG_ROW1_PORT, .position = CFG_ROW1_PIN},
    {.port = &CFG_ROW2_PORT, .position = CFG_ROW2_PIN},
    {.port = &CFG_ROW3_PORT, .position = CFG_ROW3_PIN}
};

static button_t buttonMatrix[CFG_ROWS][CFG_COLUMNS];

static void setOutput(int index)
{
    columns[index].port->DIRSET = 0x01 << columns[index].position;
}

static void setInput(int index)
{
    columns[index].port->DIRCLR = 0x01 << columns[index].position;
}

static bool readInput(int index)
{
    return (rows[index].port->IN & (0x01 << rows[index].position));
}

static void PORT_init(void)
{
    setOutput(0);
    
    for(int i = 1; i < CFG_COLUMNS; i++)
    { 
        columns[i].port->DIRCLR = (0x01 << columns[i].position);
    }
    
    for(int i = 0; i < CFG_ROWS; i++)
    {
        rows[i].port->DIRCLR = (0x01 << rows[i].position);
        *((uint8_t *)rows[i].port + BM_PORT_OFFSET + rows[i].position) = PORT_PULLUPEN_bm;
    }
}

/*
 * Button Matrix Interrupt Handler
 * This function is called every 5 ms, when the TCA OVF Interrupt is triggered
 * Scans one column of the button matrix each 5 ms and identifies an event
 */
static void buttonMatrixPhy_handler(void)
{
    static int column_index = 0;
    bool input_state = BM_BUTTON_RELEASED;
    
    if(column_index == 0)
    {
        setInput(CFG_COLUMNS - 1);
    }
    else if (column_index > 0)
    {
        setInput(column_index - 1);
    }
    
    for(int i = 0; i < CFG_ROWS; i++)
    {
        input_state = readInput(i);
        
        if(input_state == buttonMatrix[i][column_index].state)
        {
            buttonMatrix[i][column_index].debounce_count = 0;
        }
        else
        {
            buttonMatrix[i][column_index].debounce_count++;
            if(buttonMatrix[i][column_index].debounce_count == CFG_DEBOUNCE_TIME)
            {
                buttonMatrix[i][column_index].state = input_state;
                buttonMatrix[i][column_index].debounce_count = 0;
                BUTTON_MATRIX_EventHandler((column_index + (i * CFG_COLUMNS)) + 1, input_state);
            }
        }
    }
    
    column_index++;
    
    if(column_index >= CFG_COLUMNS)
    {
        column_index = 0;
    }
    
    setOutput(column_index);
}

void buttonMatrixPhy_init(void)
{
    PORT_init();
    TCA0_OverflowCallbackRegister(buttonMatrixPhy_handler);
    
    for(int i = 0; i < CFG_ROWS; i++)
    {
        for(int j = 0; j < CFG_COLUMNS; j++)
        {
            buttonMatrix[i][j].debounce_count = 0;
            buttonMatrix[i][j].state = BM_BUTTON_RELEASED;
        }
    }
}