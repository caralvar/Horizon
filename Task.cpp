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

uint8_t Task::GetTaskId()
{
    return m_u8TaskID;
}

uint8_t Task::GetReceiverTaskId()
{
    return m_u8ReceiverTaskId;
}

void Task::SetTaskPriority(uint8_t i_u8NewPriority)
{
    m_u8Priority = i_u8NewPriority;
}

void Task::SetTaskReceiverId(uint8_t i_u8ReceiverTaskId)
{
    m_u8ReceiverTaskId = i_u8ReceiverTaskId;
}
