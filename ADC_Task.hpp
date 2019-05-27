/*
 * LED.hpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */

#ifndef ADC_TASK_HPP_ 
#define ADC_TASK_HPP_
#define __NOP __nop // PREGUNTAR

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Task.hpp" // Includes parent class
#include "Mailbox.hpp"

class ADC_Task : public Task // clase heredada de tipo Task
{
    public:
        
        // Constructor prototype
        ADC_Task(Mailbox *i_ptrMailbox);
        // run prototype (inherited from the class task)
        virtual uint8_t run(void); 

        // setup prototype (inherited from the class task)
        virtual uint8_t setup(void); 

        uint8_t m_CreateAndPostMsg(void);

    private:
        Mailbox *m_ptrMailbox;
        uint16_t m_u16ResultsBuffer[32];
    protected:
};

#endif /* LED_HPP_ */  //TERMINA EL IF
 
