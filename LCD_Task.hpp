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
#include <array>

class LCD_Task : public Task // clase heredada de tipo Task
{
    public:

        // Constructor prototype
        LCD_Task(Mailbox *i_ptrMailbox);
        // run prototype (inherited from the class task)
        virtual uint8_t run(void);

        // setup prototype (inherited from the class task)
        virtual uint8_t setup(void);

        std::array<int16_t, 4>  m_GetHorizonBorderIntersection( int16_t i_i16Ax,  int16_t i_i16Az);
    private:
        Mailbox * m_ptrMailbox;
        Graphics_Context m_DisplayContext;
        int16_t m_i16indicatorHeight[2];
        int16_t m_i16Angles[2];
        std::array<std::array<int16_t, 4>, 2> m_i16Points;
    protected:
};

#endif /* LED_HPP_ */  //TERMINA EL IF

