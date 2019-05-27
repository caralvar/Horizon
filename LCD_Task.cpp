#include <LCD_Task.hpp>
#include <ADC_Task.hpp>
Graphics_Context m_DisplayContext;
uint8_t m_u8indicatorHeight[2] = { 50, 53};

LCD_Task::LCD_Task(Mailbox *i_ptrMailbox) //Constructor definition
{
    this->m_ptrMailbox = i_ptrMailbox;
}

uint8_t LCD_Task::run()  // Function Run (toggles led) definition
{

    if(m_ptrMailbox->m_CheckMailbox(this->GetTaskId()))
    {

        st_Msg l_st_MsgNewMsg = m_ptrMailbox->m_ReadMessage(this->GetTaskId());
        uint16_t l_u16ResultsBuffer[2];

        l_u16ResultsBuffer[1] = static_cast<uint16_t>(l_st_MsgNewMsg.u32MsgContent & 0x0000FFFF);
        l_u16ResultsBuffer[0] = static_cast<uint16_t>(l_st_MsgNewMsg.u32MsgContent >> 16);

        m_u8indicatorHeight[0] = conversion(&m_DisplayContext, l_u16ResultsBuffer[0]); //ALTURA ACTUAL
        if (m_u8indicatorHeight[0] > m_u8indicatorHeight[1] + 2 || m_u8indicatorHeight[0] < m_u8indicatorHeight[1] - 2)
        {
             if (m_u8indicatorHeight[0] > m_u8indicatorHeight[1])
             {
                 int i;
                 Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_BLUE);     // FOREGROUND COLOR (PINTA)
                 for (i = 0; i < m_u8indicatorHeight[0] - m_u8indicatorHeight[1] + 1; i++)
                 {
                     Graphics_drawLineH(&m_DisplayContext, 0, Graphics_getDisplayWidth(&m_DisplayContext), m_u8indicatorHeight[0] - i);
                 }

             }
             else
             {
                 int i;
                 Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_GREEN);     // FOREGROUND COLOR (PINTA)
                 for (i = 0; i < m_u8indicatorHeight[1] - m_u8indicatorHeight[0] + 1; i++)
                 {
                     Graphics_drawLineH(&m_DisplayContext, 0, Graphics_getDisplayWidth(&m_DisplayContext), m_u8indicatorHeight[0] + i);
                 }
             }
             m_u8indicatorHeight[1] = m_u8indicatorHeight[0];
        }
        return(NO_ERR);
    }
}

uint8_t LCD_Task::setup() // PORT SETUP definition
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP); // ORIENTACION SIEMPRE HACIA ARRIBA

    /* Initializes graphics context */
    Graphics_initContext(&m_DisplayContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_GREEN);     // FOREGROUND COLOR (PINTA)
    Graphics_setBackgroundColor(&m_DisplayContext, GRAPHICS_COLOR_BLUE); // BACKGROUND COLOR
    GrContextFontSet(&m_DisplayContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&m_DisplayContext);
    //drawTitle();
    return(NO_ERR);
}


uint8_t LCD_Task::conversion(Graphics_Context *ctxt, uint16_t x)
{
    float m = 0 - Graphics_getDisplayHeight(ctxt)/(11440.0 - 4900.0);
    float b = -m * 11440.0;
    return (uint8_t) (m * x + b) ;
}
