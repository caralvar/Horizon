#include <LCD_Task.hpp>
#include <ADC_Task.hpp>
Graphics_Context m_DisplayContext;
uint8_t m_i16indicatorHeight[2] = { 50, 53};

LCD_Task::LCD_Task(Mailbox *i_ptrMailbox) //Constructor definition
{
    this->m_ptrMailbox = i_ptrMailbox;
}

uint8_t LCD_Task::run()  // Function Run (toggles led) definition
{

    if(m_ptrMailbox->m_CheckMailbox(this->GetTaskId()))
    {

        st_Msg l_st_MsgNewMsg = m_ptrMailbox->m_ReadMessage(this->GetTaskId());
        int16_t l_u16ResultsBuffer[2];

        l_u16ResultsBuffer[0] = static_cast<int16_t>(l_st_MsgNewMsg.u32MsgContent & 0x0000FFFF);
        l_u16ResultsBuffer[1] = static_cast<int16_t>(l_st_MsgNewMsg.u32MsgContent >> 16);

        m_i16Angles[0] = l_u16ResultsBuffer[0] - 90;
        m_i16Angles[1] = l_u16ResultsBuffer[1] - 90;

        m_i16Points[0] = m_GetHorizonBorderIntersection( m_i16Angles[0],  m_i16Angles[1]);

        m_i16indicatorHeight[0] = (uint8_t) (m_i16Angles[1] * (128.0/180.0) + 64.0);

        if (m_i16indicatorHeight[0] < 5) m_i16indicatorHeight[0] = 0;
        if (m_i16indicatorHeight[0] > 123) m_i16indicatorHeight[0] = 128;

        if (m_i16indicatorHeight[0] > m_i16indicatorHeight[1] + 2 || m_i16indicatorHeight[0] < m_i16indicatorHeight[1] - 2 ||
                m_i16Points[0][0] > m_i16Points[1][0] + 2 || m_i16Points[0][0] < m_i16Points[1][0] - 2 ||
                m_i16Points[0][1] > m_i16Points[1][1] + 2 || m_i16Points[0][1] < m_i16Points[1][1] - 2)
        {
            struct Graphics_Rectangle l_blueRectangle = { 0, 0, 128, m_i16indicatorHeight[0]};
            struct Graphics_Rectangle l_greenRectangle = { 0, m_i16indicatorHeight[0], 128, 128};
            Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_GREEN);
            Graphics_fillRectangle(&m_DisplayContext, &l_greenRectangle);
            Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_BLUE);
            Graphics_fillRectangle(&m_DisplayContext, &l_blueRectangle);
            Graphics_setForegroundColor(&m_DisplayContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&m_DisplayContext, m_i16Points[0][0], m_i16Points[0][1],m_i16Points[0][2], m_i16Points[0][3]);
            Graphics_drawLine(&m_DisplayContext, m_i16Points[0][0], m_i16Points[0][1] + 1,m_i16Points[0][2], m_i16Points[0][3] + 1);
            m_i16indicatorHeight[1] = m_i16indicatorHeight[0];
            m_i16Points[1] = m_i16Points[0];
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


std::array<int16_t, 4>  LCD_Task::m_GetHorizonBorderIntersection( int16_t i_i16Ax,  int16_t i_i16Az)
{
    std::array<int16_t, 4> l_i16Result;
       uint8_t l_u8Height;
       l_u8Height = (uint8_t) (i_i16Az * (128.0/180.0) + 64.0);

       // Full arriba
       if (i_i16Az > 80)
       {
           //Izqu
           l_i16Result[0] = 0;
           l_i16Result[1] = 128;
           //Dere
           l_i16Result[2] = 128;
           l_i16Result[3] = 128;
           return l_i16Result;
       }
       // Full abajo
       else if (i_i16Az < -80)
       {
           //Izqu
           l_i16Result[0] = 0;
           l_i16Result[1] = 0;
           //Dere
           l_i16Result[2] = 128;
           l_i16Result[3] = 0;
           return l_i16Result;
       }

       //Normal
       if (i_i16Ax >= -45 && i_i16Ax <= 45)
       {
           //Izqu
           l_i16Result[0] = 0;
           l_i16Result[1] = (int16_t) (l_u8Height - 64 * tan(i_i16Ax * PI / 180));
           //Dere
           l_i16Result[2] = 128;
           l_i16Result[3] = (int16_t) (l_u8Height + 64 * tan(i_i16Ax * PI / 180));
       }
       // Inclinacion derecha
       else if (i_i16Ax >= -75 && i_i16Ax < -45)
       {
           //Izqu
           l_i16Result[0] = (int16_t) (64 - 64 * tan((90 + i_i16Ax) * PI / 180));
           l_i16Result[1] = 128;
           //Dere
           l_i16Result[2] = (int16_t) (64 + 64 * tan((90 + i_i16Ax) * PI / 180));
           l_i16Result[3] = 0;
       }
       // Inclinacion izquierda
       else if (i_i16Ax > 45 && i_i16Ax <= 75)
       {
           //Izqu
           l_i16Result[0] = (int16_t) (64 - 64 * tan((90 - i_i16Ax) * PI / 180));
           l_i16Result[1] = 0;
           //Dere
           l_i16Result[2] = (int16_t) (64 + 64 * tan((90 - i_i16Ax) * PI / 180));
           l_i16Result[3] = 128;
       }
       // Full derecha
       else if (i_i16Ax < -75)
       {
           //Izqu
           l_i16Result[0] = 64;
           l_i16Result[1] = 128;
           //Dere
           l_i16Result[2] = 64;
           l_i16Result[3] = 0;
       }
       // Full izquierda
       else if (i_i16Ax > 75)
       {
           //Izqu
           l_i16Result[0] = 64;
           l_i16Result[1] = 0;
           //Dere
           l_i16Result[2] = 64;
           l_i16Result[3] = 128;
       }
       return l_i16Result;
}

