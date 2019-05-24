#include "Task.hpp"

Task::Task()    // Constructor
{
    m_u8TaskID = m_u8NextTaskID; // Set task ID as NextTaskID
    m_bIsFinished = false;       // Set Finished flag as false
    m_u8NextTaskID++; // Update next task id;
}

bool Task::IsTaskFinished()
{
    return m_bIsFinished;
}

uint8_t Task::GetTaskPriority()
{
    return m_u8Priority;
}

void Task::SetTaskPriority(uint8_t i_u8NewPriority)
{
    m_u8Priority = i_u8NewPriority;
}

