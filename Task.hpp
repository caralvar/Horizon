#ifndef TASK_HPP_
#define TASK_HPP_

#include <ti/devices/msp432p4xx/inc/msp.h>

#define NO_ERR 0
#define RET_ERR 1

class Task
{
    public:
        // Attribute task ID
        uint8_t m_u8TaskID; // Why public?

        // Constructor prototype
        Task();

        // Run function prototype (virtual for inheritance)
        virtual uint8_t run(void)
        {
            return 0;
        };

        // Setup function prototype (virtual for inheritance)
        virtual uint8_t setup(void)
        {
            return 0;
        };

        /* Getters */
        // Return Task finished flag
        bool IsTaskFinished(void);
        // Get task priority
        uint8_t GetTaskPriority(void);

        uint8_t GetTaskId(void);
        uint8_t GetReceiverTaskId(void);
        /*Setters*/
        // Set task priority function (defined on .hpp Why?)
        void SetTaskPriority(uint8_t i_u8NewPriority);
        // Set task msg receiver
        void SetTaskReceiverId(uint8_t i_u8ReceiverTaskId);
    private:
        /* Private attributes */
       static uint8_t m_u8NextTaskID; // ID de la proxima tarea
       uint8_t m_u8Priority;             // Prioridad de la tarea
       uint8_t m_u8ReceiverTaskId;
    protected:                               // Why protected
       bool m_bIsFinished;               //PREGUNTAR
};

#endif /* TASK_HPP_ */
