#include <ADC_Task.hpp>


ADC_Task::ADC_Task(Mailbox * i_ptrMailbox) //Constructor definition
{
    this->m_ptrMailbox = i_ptrMailbox;
}

uint8_t ADC_Task::run()  // Function Run (toggles led) definition ADC14_getEnabledInterruptStatus
{
    uint64_t status;

        status = MAP_ADC14_getEnabledInterruptStatus();
        MAP_ADC14_clearInterruptFlag(status);

        // Reads conversion result values
        if(status & (ADC_INT0 | ADC_INT1 | ADC_INT2))
        {
            /* Store ADC14 conversion results */
            m_u16ResultsBuffer[0] = ADC14_getResult(ADC_MEM0); //z
            m_u16ResultsBuffer[1] = ADC14_getResult(ADC_MEM1); //y
            m_u16ResultsBuffer[2] = ADC14_getResult(ADC_MEM2); //x
        }

        this->m_CreateAndPostMsg();
    return(NO_ERR);
}

uint8_t ADC_Task::setup() // PORT SETUP definition
{
    // Setup from the example http://dev.ti.com/tirex/explore/node?node=AD7fp0zahQovr1tZ1p6Qbw__z-lQYNj__LATEST
    // at TI resource explorer

    /* Configures Pin 4.0, 4.2, and 6.1 as ADC input */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

    /* Initializing ADC (ADCOSC/64/8) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8,
            0);

    /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM2 (A11, A13, A14)  with no repeat)
         * with internal 2.5v reference */ // ADC14_configureConversionMemory
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0 | ADC_MEM1 | ADC_MEM2,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

    MAP_ADC14_configureConversionMemory(ADC_MEM2,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);

    /* Enabling the interrupt when a conversion on channel 2 (end of sequence)
     *  is complete and enabling conversions */
    MAP_ADC14_enableInterrupt(ADC_INT2);

    /* Enabling Interrupts */
    //MAP_Interrupt_enableInterrupt(INT_ADC14);
    //MAP_Interrupt_enableMaster();

    /* Setting up the sample timer to automatically step through the sequence
     * convert.
     */
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

    return (NO_ERR);
}


uint8_t ADC_Task::m_CreateAndPostMsg()
{
    //Create Msg
    st_Msg l_MsgToSend;
    // Construct content
    l_MsgToSend.u32MsgContent = static_cast<uint16_t>(m_GetAngle(m_u16ResultsBuffer[2]));
    l_MsgToSend.u32MsgContent = l_MsgToSend.u32MsgContent << 16;
    l_MsgToSend.u32MsgContent += static_cast<uint16_t>(m_GetAngle(m_u16ResultsBuffer[0]));
    //To
    l_MsgToSend.u8ToId = this->GetReceiverTaskId();
    //From
    l_MsgToSend.u8FromId = this->GetTaskId();
    //Post
    m_ptrMailbox->m_PostMessage(l_MsgToSend);
    return (NO_ERR);
}

// Calculates axis angle respect to g
uint16_t ADC_Task::m_GetAngle(uint16_t i_u16Axis)
{
    float l_fDiv;
    l_fDiv = (i_u16Axis - 8220.0) / 3170.0;
    if (l_fDiv < -1.0) l_fDiv = -1.0;
    if (l_fDiv > 1.0) l_fDiv = 1.0;
    return (uint16_t) (acos(l_fDiv) * 180.0 / PI);
}
