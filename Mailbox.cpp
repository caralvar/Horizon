#include "Mailbox.hpp"

Mailbox::Mailbox(){};

uint8_t Mailbox::m_PostMessage(st_Msg i_st_Msg_incomingMsg)
{
    uint8_t l_u8ReceiverId = i_st_Msg_incomingMsg.u8ToId;
    m_arrSt_Msg_CurrentMessages[l_u8ReceiverId][m_arrU8_messageCounter[l_u8ReceiverId]] = i_st_Msg_incomingMsg;
    m_arrU8_messageCounter[l_u8ReceiverId]++;
    return NO_ERR;
}


st_Msg Mailbox::m_ReadMessage(uint8_t i_u8TaskID)
{
    m_arrU8_messageCounter[i_u8TaskID]--;
    return m_arrSt_Msg_CurrentMessages[i_u8TaskID][m_arrU8_messageCounter[i_u8TaskID]];
}


bool Mailbox::m_CheckMailbox(uint8_t i_u8TaskID)
{
    return (bool) m_arrU8_messageCounter[i_u8TaskID];
}
