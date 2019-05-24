#include <LCD_Task.hpp>
#include <ADC_Task.hpp>
Graphics_Context g_sContext;
uint8_t indicatorHeight[2] = { 50, 53};

LCD_Task::LCD_Task(int i) //Constructor definition
{

}

uint8_t LCD_Task::run()  // Function Run (toggles led) definition
{
    //indicatorHeight[0] = conversion(&g_sContext, resultsBuffer[2]); //ALTURA ACTUAL
    if (indicatorHeight[0] > indicatorHeight[1] + 2 || indicatorHeight[0] < indicatorHeight[1] - 2)
    {
         if (indicatorHeight[0] > indicatorHeight[1])
         {
             int i;
             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);     // FOREGROUND COLOR (PINTA)
             for (i = 0; i < indicatorHeight[0] - indicatorHeight[1] + 1; i++)
             {
                 Graphics_drawLineH(&g_sContext, 0, Graphics_getDisplayWidth(&g_sContext), indicatorHeight[0] - i);
             }

         }
         else
         {
             int i;
             Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);     // FOREGROUND COLOR (PINTA)
             for (i = 0; i < indicatorHeight[1] - indicatorHeight[0] + 1; i++)
             {
                 Graphics_drawLineH(&g_sContext, 0, Graphics_getDisplayWidth(&g_sContext), indicatorHeight[0] + i);
             }
         }
         indicatorHeight[1] = indicatorHeight[0];
    }
    return(NO_ERR);
}

uint8_t LCD_Task::setup() // PORT SETUP definition
{
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP); // ORIENTACION SIEMPRE HACIA ARRIBA

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);     // FOREGROUND COLOR (PINTA)
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE); // BACKGROUND COLOR
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
    //drawTitle();
    return(NO_ERR);
}


uint8_t LCD_Task::conversion(Graphics_Context *ctxt, uint16_t x)
{
    float m = 0 - Graphics_getDisplayHeight(ctxt)/(11440.0 - 4900.0);
    float b = -m * 11440.0;
    return (uint8_t) (m * x + b) ;
}
