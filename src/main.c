/*
 * main.c
 *
 *  Created on: 05-Jun-2024
 *      Author: Arunava Karmakar
 *        mail: arunava.karmakar@protonmail.ch
 */

//*****************************************************************************
//
// Control the D3 and D4 led with USR-SW1 and USR_SW2
// glow D3 when USR-SW1 is pressed
//
// D3       ---> PF4
// D4       ---> PF0
// USR-SW1  ---> PJ0
// USR-SW2  ---> PJ1
//
// pull-up resistor - if button is released, signal is high and low if pressed
//
//*****************************************************************************

#include "TM4C129ENCPDT.h"                    // Device header

#include "tm4c129encpdt_port.h"

int main(void)
{

    uint8_t USR_SW1_state, USR_SW2_state;

    SYSCTL->RCGCGPIO = (SYSCTL->RCGCGPIO) | (1 << GPIO_PORT_F) | (1 << GPIO_PORT_J); // enable clock for PF and PJ

    GPIOF_AHB->DEN = GPIOF_AHB->DEN | (1 << GPIO_PORT_PIN_0) | (1 << GPIO_PORT_PIN_4); // set PF0 and PF4 and digital pins
    GPIOF_AHB->DIR = GPIOF_AHB->DIR | (1 << GPIO_PORT_PIN_0) | (1 << GPIO_PORT_PIN_4); // set PF0 and PF4 as OP

    GPIOJ_AHB->PUR = GPIOJ_AHB->PUR | (1 << GPIO_PORT_PIN_0) | (1 << GPIO_PORT_PIN_1); // enable the weak pull-up resistor on PJ0 and PJ1
    GPIOJ_AHB->DEN = GPIOJ_AHB->DEN | (1 << GPIO_PORT_PIN_0) | (1 << GPIO_PORT_PIN_1); // set PJ0 and PJ1 and digital pins
    GPIOJ_AHB->DIR = GPIOJ_AHB->DIR & (~(1 << GPIO_PORT_PIN_0)) & (~(1 << GPIO_PORT_PIN_1)); // set PJ0 and PJ1 as IP

    while(1) {
        USR_SW1_state = (GPIOJ_AHB->DATA & (1 << GPIO_PORT_PIN_0)) >> GPIO_PORT_PIN_0; // read state of USR_SW1
        if(USR_SW1_state == 0) { // if USR_SW1 is pressed
            GPIOF_AHB->DATA = GPIOF_AHB->DATA | (1 << GPIO_PORT_PIN_4); // high on PF4
            GPIOF_AHB->DATA = GPIOF_AHB->DATA & ~(1 << GPIO_PORT_PIN_0); // low on PF0
        }/* else {
            GPIOF_AHB->DATA = GPIOF_AHB->DATA & ~(1 << GPIO_PORT_PIN_4); // low on PF4
        }*/

        USR_SW2_state = (GPIOJ_AHB->DATA & (1 << GPIO_PORT_PIN_1)) >> GPIO_PORT_PIN_1; // read state of USR_SW2
        if(USR_SW2_state == 0) { // if USR_SW2 is pressed
            GPIOF_AHB->DATA = GPIOF_AHB->DATA & ~(1 << GPIO_PORT_PIN_4); // low on PF4
            GPIOF_AHB->DATA = GPIOF_AHB->DATA | (1 << GPIO_PORT_PIN_0); // high on PF0
        }/* else {
            GPIOF_AHB->DATA = GPIOF_AHB->DATA & ~(1 << GPIO_PORT_PIN_0); // low on PF0
        }*/
    }
}
