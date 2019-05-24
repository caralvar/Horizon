/*
 * LED.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef ADC_TASK_HPP_ 
#define ADC_TASK_HPP_
#define __NOP __nop // PREGUNTAR

#include <LcdDriver/Crystalfontz128x128_ST7735.hpp>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include <stdio.h>
#include "Task.hpp" // Includes parent class


class ADC_Task : public Task // clase heredada de tipo Task
{
    public:
        
        // Constructor prototype
        ADC_Task(int i);
        // run prototype (inherited from the class task)
        virtual uint8_t run(void); 

        // setup prototype (inherited from the class task)
        virtual uint8_t setup(void); 

    private:


    protected:
};

#endif /* LED_HPP_ */  //TERMINA EL IF
 
