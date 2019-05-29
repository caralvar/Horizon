/*
 * LCD_Task
 *  Interprets ADC messages and translates them to useful graphics on the screen
 *  in order to make a horizon indicator.
 *
 *      Author: Carlos Alvarado
 *              Daniel Diaz
 */

#ifndef LCD_TASK_HPP_
#define LCD_TASK_HPP_
#define __NOP __nop // PREGUNTAR

// LCD and graphics libraries
#include <LcdDriver/Crystalfontz128x128_ST7735.hpp>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
// Includes mailbox
#include "Mailbox.hpp"
// Includes parent class
#include "Task.hpp"
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

        // Determines intersection points between the horizon line and the borders of the screen
        std::array<int16_t, 4>  m_GetHorizonBorderIntersection( int16_t i_i16Ax,  int16_t i_i16Az);
    private:
        Mailbox * m_ptrMailbox; // Pointer to mailbox
        Graphics_Context m_DisplayContext;  // Display's Context
        int16_t m_i16indicatorHeight[2];    // Current and last horizon line height
        int16_t m_i16Angles[2];             // Current inclination angles respect to the x and z axis
        // Last and current intersection points between the horizon line and the borders of the screen
        std::array<std::array<int16_t, 4>, 2> m_i16Points;
    protected:
};

#endif /* LCD_Task_HPP_ */  //TERMINA EL IF

