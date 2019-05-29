/*
 * mailbox.hpp
 *
 * Mailbox objects allows communication between tasks.
 *      Author: Carlos Alvarado
 *              Daniel Diaz
 */

#ifndef MAILBOX_HPP_ 
#define MAILBOX_HPP_
#define __NOP __nop // PREGUNTAR
#define NO_ERR 0
#define RET_ERR 1
#define MSG_SLOTS       10        // Mailbox size per Task
#define NUMBER_OF_SLOTS       255 // Same as available Task IDs
#include <array>

// - This structure defines the messages format
struct st_Msg {
    uint8_t u8FromId;
    uint8_t u8ToId;
    uint32_t u32MsgContent;
};

class Mailbox 
{
    public:
        Mailbox();
        uint8_t m_PostMessage(st_Msg);
        st_Msg m_ReadMessage(uint8_t i_u8TaskID);
        bool m_CheckMailbox(uint8_t i_u8TaskID);

    private:
        std::array<uint8_t, NUMBER_OF_SLOTS> m_arrU8_messageCounter; // Counts number of messages in mailbox per task
        std::array<std::array<st_Msg, MSG_SLOTS>, NUMBER_OF_SLOTS> m_arrSt_Msg_CurrentMessages; // Allocates current messages on mailbox
        bool m_bMailboxEmpty;
    protected:
};

#endif /* MAILBOX_HPP_ */  
 
