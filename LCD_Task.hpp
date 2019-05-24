/*
 * LED.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef LCD_TASK_HPP_
#define LCD_TASK_HPP_
#define __NOP __nop // PREGUNTAR

#include <LcdDriver/Crystalfontz128x128_ST7735.hpp>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include <ADC_Task.hpp>
#include "Task.hpp" // Includes parent class


class LCD_Task : public Task // clase heredada de tipo Task
{
    public:

        // Constructor prototype
        LCD_Task(int i);
        // run prototype (inherited from the class task)
        virtual uint8_t run(void);

        // setup prototype (inherited from the class task)
        virtual uint8_t setup(void);

        uint8_t conversion(Graphics_Context *ctxt, uint16_t x);


    private:


    protected:
};

#endif /* LED_HPP_ */  //TERMINA EL IF

