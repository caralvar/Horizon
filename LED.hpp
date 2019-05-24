/*
 * LED.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef LED_HPP_ 
#define LED_HPP_
#define __NOP __nop // PREGUNTAR

#include <LcdDriver/Crystalfontz128x128_ST7735.hpp>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include "Task.hpp" // Includes parent class


class LED : public Task // clase heredada de tipo Task
{
    public:
        
        // Constructor prototype
        LED(uint16_t i_BITN); 

        // run prototype (inherited from the class task)
        virtual uint8_t run(void); 

        // setup prototype (inherited from the class task)
        virtual uint8_t setup(void); 

    private:

        // Private attribute led to toggle
        uint16_t m_u16BITN; // LED BIT

    protected:
};

#endif /* LED_HPP_ */  //TERMINA EL IF
 