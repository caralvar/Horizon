#include "Mailbox.hpp"

// Mailbox constructor
Mailbox::Mailbox(){};

// - The post function, if there's space available saves the new message in the mailbox of the corresponding receiver
uint8_t Mailbox::m_PostMessage(st_Msg i_st_Msg_incomingMsg)
{
    uint8_t l_u8ReceiverId = i_st_Msg_incomingMsg.u8ToId;
    if (m_arrU8_messageCounter[l_u8ReceiverId] == MSG_SLOTS) return (RET_ERR); // Returns error if there's no space available
    m_arrSt_Msg_CurrentMessages[l_u8ReceiverId][m_arrU8_messageCounter[l_u8ReceiverId]] = i_st_Msg_incomingMsg;
    m_arrU8_messageCounter[l_u8ReceiverId]++;
    return NO_ERR;
}

// - The read function, reads last posted message and frees space
st_Msg Mailbox::m_ReadMessage(uint8_t i_u8TaskID)
{
    m_arrU8_messageCounter[i_u8TaskID]--;
    return m_arrSt_Msg_CurrentMessages[i_u8TaskID][m_arrU8_messageCounter[i_u8TaskID]];
}

// - Returns true if there are unread messages.
bool Mailbox::m_CheckMailbox(uint8_t i_u8TaskID)
{
    return (bool) m_arrU8_messageCounter[i_u8TaskID];
}
