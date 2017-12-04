/*******************************************************************************
* File Name: NeckHandle.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "NeckHandle.h"

/* Error message for removed <resource> through optimization */
#ifdef NeckHandle_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* NeckHandle_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 NeckHandle_initVar = 0u;


/*******************************************************************************
* Function Name: NeckHandle_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NeckHandle_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void NeckHandle_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(NeckHandle_initVar == 0u)
    {
        NeckHandle_Init();
        NeckHandle_initVar = 1u;
    }
    NeckHandle_Enable();

}


/*******************************************************************************
* Function Name: NeckHandle_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  NeckHandle_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void NeckHandle_Init(void) 
{
    #if (NeckHandle_UsingFixedFunction || NeckHandle_UseControl)
        uint8 ctrl;
    #endif /* (NeckHandle_UsingFixedFunction || NeckHandle_UseControl) */

    #if(!NeckHandle_UsingFixedFunction)
        #if(NeckHandle_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 NeckHandle_interruptState;
        #endif /* (NeckHandle_UseStatus) */
    #endif /* (!NeckHandle_UsingFixedFunction) */

    #if (NeckHandle_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        NeckHandle_CONTROL |= NeckHandle_CFG0_MODE;
        #if (NeckHandle_DeadBand2_4)
            NeckHandle_CONTROL |= NeckHandle_CFG0_DB;
        #endif /* (NeckHandle_DeadBand2_4) */

        ctrl = NeckHandle_CONTROL3 & ((uint8 )(~NeckHandle_CTRL_CMPMODE1_MASK));
        NeckHandle_CONTROL3 = ctrl | NeckHandle_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        NeckHandle_RT1 &= ((uint8)(~NeckHandle_RT1_MASK));
        NeckHandle_RT1 |= NeckHandle_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        NeckHandle_RT1 &= ((uint8)(~NeckHandle_SYNCDSI_MASK));
        NeckHandle_RT1 |= NeckHandle_SYNCDSI_EN;

    #elif (NeckHandle_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = NeckHandle_CONTROL & ((uint8)(~NeckHandle_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~NeckHandle_CTRL_CMPMODE1_MASK));
        NeckHandle_CONTROL = ctrl | NeckHandle_DEFAULT_COMPARE2_MODE |
                                   NeckHandle_DEFAULT_COMPARE1_MODE;
    #endif /* (NeckHandle_UsingFixedFunction) */

    #if (!NeckHandle_UsingFixedFunction)
        #if (NeckHandle_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            NeckHandle_AUX_CONTROLDP0 |= (NeckHandle_AUX_CTRL_FIFO0_CLR);
        #else /* (NeckHandle_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            NeckHandle_AUX_CONTROLDP0 |= (NeckHandle_AUX_CTRL_FIFO0_CLR);
            NeckHandle_AUX_CONTROLDP1 |= (NeckHandle_AUX_CTRL_FIFO0_CLR);
        #endif /* (NeckHandle_Resolution == 8) */

        NeckHandle_WriteCounter(NeckHandle_INIT_PERIOD_VALUE);
    #endif /* (!NeckHandle_UsingFixedFunction) */

    NeckHandle_WritePeriod(NeckHandle_INIT_PERIOD_VALUE);

        #if (NeckHandle_UseOneCompareMode)
            NeckHandle_WriteCompare(NeckHandle_INIT_COMPARE_VALUE1);
        #else
            NeckHandle_WriteCompare1(NeckHandle_INIT_COMPARE_VALUE1);
            NeckHandle_WriteCompare2(NeckHandle_INIT_COMPARE_VALUE2);
        #endif /* (NeckHandle_UseOneCompareMode) */

        #if (NeckHandle_KillModeMinTime)
            NeckHandle_WriteKillTime(NeckHandle_MinimumKillTime);
        #endif /* (NeckHandle_KillModeMinTime) */

        #if (NeckHandle_DeadBandUsed)
            NeckHandle_WriteDeadTime(NeckHandle_INIT_DEAD_TIME);
        #endif /* (NeckHandle_DeadBandUsed) */

    #if (NeckHandle_UseStatus || NeckHandle_UsingFixedFunction)
        NeckHandle_SetInterruptMode(NeckHandle_INIT_INTERRUPTS_MODE);
    #endif /* (NeckHandle_UseStatus || NeckHandle_UsingFixedFunction) */

    #if (NeckHandle_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        NeckHandle_GLOBAL_ENABLE |= NeckHandle_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        NeckHandle_CONTROL2 |= NeckHandle_CTRL2_IRQ_SEL;
    #else
        #if(NeckHandle_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            NeckHandle_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            NeckHandle_STATUS_AUX_CTRL |= NeckHandle_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(NeckHandle_interruptState);

            /* Clear the FIFO to enable the NeckHandle_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            NeckHandle_ClearFIFO();
        #endif /* (NeckHandle_UseStatus) */
    #endif /* (NeckHandle_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: NeckHandle_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void NeckHandle_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (NeckHandle_UsingFixedFunction)
        NeckHandle_GLOBAL_ENABLE |= NeckHandle_BLOCK_EN_MASK;
        NeckHandle_GLOBAL_STBY_ENABLE |= NeckHandle_BLOCK_STBY_EN_MASK;
    #endif /* (NeckHandle_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (NeckHandle_UseControl || NeckHandle_UsingFixedFunction)
        NeckHandle_CONTROL |= NeckHandle_CTRL_ENABLE;
    #endif /* (NeckHandle_UseControl || NeckHandle_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: NeckHandle_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void NeckHandle_Stop(void) 
{
    #if (NeckHandle_UseControl || NeckHandle_UsingFixedFunction)
        NeckHandle_CONTROL &= ((uint8)(~NeckHandle_CTRL_ENABLE));
    #endif /* (NeckHandle_UseControl || NeckHandle_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (NeckHandle_UsingFixedFunction)
        NeckHandle_GLOBAL_ENABLE &= ((uint8)(~NeckHandle_BLOCK_EN_MASK));
        NeckHandle_GLOBAL_STBY_ENABLE &= ((uint8)(~NeckHandle_BLOCK_STBY_EN_MASK));
    #endif /* (NeckHandle_UsingFixedFunction) */
}

#if (NeckHandle_UseOneCompareMode)
    #if (NeckHandle_CompareMode1SW)


        /*******************************************************************************
        * Function Name: NeckHandle_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void NeckHandle_SetCompareMode(uint8 comparemode) 
        {
            #if(NeckHandle_UsingFixedFunction)

                #if(0 != NeckHandle_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << NeckHandle_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != NeckHandle_CTRL_CMPMODE1_SHIFT) */

                NeckHandle_CONTROL3 &= ((uint8)(~NeckHandle_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                NeckHandle_CONTROL3 |= comparemodemasked;

            #elif (NeckHandle_UseControl)

                #if(0 != NeckHandle_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << NeckHandle_CTRL_CMPMODE1_SHIFT)) &
                                                NeckHandle_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & NeckHandle_CTRL_CMPMODE1_MASK;
                #endif /* (0 != NeckHandle_CTRL_CMPMODE1_SHIFT) */

                #if(0 != NeckHandle_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << NeckHandle_CTRL_CMPMODE2_SHIFT)) &
                                               NeckHandle_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & NeckHandle_CTRL_CMPMODE2_MASK;
                #endif /* (0 != NeckHandle_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                NeckHandle_CONTROL &= ((uint8)(~(NeckHandle_CTRL_CMPMODE1_MASK |
                                            NeckHandle_CTRL_CMPMODE2_MASK)));
                NeckHandle_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (NeckHandle_UsingFixedFunction) */
        }
    #endif /* NeckHandle_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (NeckHandle_CompareMode1SW)


        /*******************************************************************************
        * Function Name: NeckHandle_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void NeckHandle_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != NeckHandle_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << NeckHandle_CTRL_CMPMODE1_SHIFT)) &
                                           NeckHandle_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & NeckHandle_CTRL_CMPMODE1_MASK;
            #endif /* (0 != NeckHandle_CTRL_CMPMODE1_SHIFT) */

            #if (NeckHandle_UseControl)
                NeckHandle_CONTROL &= ((uint8)(~NeckHandle_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                NeckHandle_CONTROL |= comparemodemasked;
            #endif /* (NeckHandle_UseControl) */
        }
    #endif /* NeckHandle_CompareMode1SW */

#if (NeckHandle_CompareMode2SW)


    /*******************************************************************************
    * Function Name: NeckHandle_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != NeckHandle_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << NeckHandle_CTRL_CMPMODE2_SHIFT)) &
                                                 NeckHandle_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & NeckHandle_CTRL_CMPMODE2_MASK;
        #endif /* (0 != NeckHandle_CTRL_CMPMODE2_SHIFT) */

        #if (NeckHandle_UseControl)
            NeckHandle_CONTROL &= ((uint8)(~NeckHandle_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            NeckHandle_CONTROL |= comparemodemasked;
        #endif /* (NeckHandle_UseControl) */
    }
    #endif /*NeckHandle_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!NeckHandle_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: NeckHandle_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void NeckHandle_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(NeckHandle_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: NeckHandle_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 NeckHandle_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(NeckHandle_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(NeckHandle_CAPTURE_LSB_PTR));
    }

    #if (NeckHandle_UseStatus)


        /*******************************************************************************
        * Function Name: NeckHandle_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void NeckHandle_ClearFIFO(void) 
        {
            while(0u != (NeckHandle_ReadStatusRegister() & NeckHandle_STATUS_FIFONEMPTY))
            {
                (void)NeckHandle_ReadCapture();
            }
        }

    #endif /* NeckHandle_UseStatus */

#endif /* !NeckHandle_UsingFixedFunction */


/*******************************************************************************
* Function Name: NeckHandle_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void NeckHandle_WritePeriod(uint16 period) 
{
    #if(NeckHandle_UsingFixedFunction)
        CY_SET_REG16(NeckHandle_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(NeckHandle_PERIOD_LSB_PTR, period);
    #endif /* (NeckHandle_UsingFixedFunction) */
}

#if (NeckHandle_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: NeckHandle_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void NeckHandle_WriteCompare(uint16 compare) \
                                       
    {
        #if(NeckHandle_UsingFixedFunction)
            CY_SET_REG16(NeckHandle_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(NeckHandle_COMPARE1_LSB_PTR, compare);
        #endif /* (NeckHandle_UsingFixedFunction) */

        #if (NeckHandle_PWMMode == NeckHandle__B_PWM__DITHER)
            #if(NeckHandle_UsingFixedFunction)
                CY_SET_REG16(NeckHandle_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(NeckHandle_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (NeckHandle_UsingFixedFunction) */
        #endif /* (NeckHandle_PWMMode == NeckHandle__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: NeckHandle_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_WriteCompare1(uint16 compare) \
                                        
    {
        #if(NeckHandle_UsingFixedFunction)
            CY_SET_REG16(NeckHandle_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(NeckHandle_COMPARE1_LSB_PTR, compare);
        #endif /* (NeckHandle_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: NeckHandle_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_WriteCompare2(uint16 compare) \
                                        
    {
        #if(NeckHandle_UsingFixedFunction)
            CY_SET_REG16(NeckHandle_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(NeckHandle_COMPARE2_LSB_PTR, compare);
        #endif /* (NeckHandle_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (NeckHandle_DeadBandUsed)


    /*******************************************************************************
    * Function Name: NeckHandle_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!NeckHandle_DeadBand2_4)
            CY_SET_REG8(NeckHandle_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            NeckHandle_DEADBAND_COUNT &= ((uint8)(~NeckHandle_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(NeckHandle_DEADBAND_COUNT_SHIFT)
                NeckHandle_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << NeckHandle_DEADBAND_COUNT_SHIFT)) &
                                                    NeckHandle_DEADBAND_COUNT_MASK;
            #else
                NeckHandle_DEADBAND_COUNT |= deadtime & NeckHandle_DEADBAND_COUNT_MASK;
            #endif /* (NeckHandle_DEADBAND_COUNT_SHIFT) */

        #endif /* (!NeckHandle_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: NeckHandle_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 NeckHandle_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!NeckHandle_DeadBand2_4)
            return (CY_GET_REG8(NeckHandle_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(NeckHandle_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(NeckHandle_DEADBAND_COUNT & NeckHandle_DEADBAND_COUNT_MASK)) >>
                                                                           NeckHandle_DEADBAND_COUNT_SHIFT));
            #else
                return (NeckHandle_DEADBAND_COUNT & NeckHandle_DEADBAND_COUNT_MASK);
            #endif /* (NeckHandle_DEADBAND_COUNT_SHIFT) */
        #endif /* (!NeckHandle_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (NeckHandle_UseStatus || NeckHandle_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: NeckHandle_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(NeckHandle_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: NeckHandle_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 NeckHandle_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(NeckHandle_STATUS_PTR));
    }

#endif /* (NeckHandle_UseStatus || NeckHandle_UsingFixedFunction) */


#if (NeckHandle_UseControl)


    /*******************************************************************************
    * Function Name: NeckHandle_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 NeckHandle_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(NeckHandle_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: NeckHandle_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(NeckHandle_CONTROL_PTR, control);
    }

#endif /* (NeckHandle_UseControl) */


#if (!NeckHandle_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: NeckHandle_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 NeckHandle_ReadCapture(void) 
    {
        return (CY_GET_REG16(NeckHandle_CAPTURE_LSB_PTR));
    }

#endif /* (!NeckHandle_UsingFixedFunction) */


#if (NeckHandle_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: NeckHandle_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 NeckHandle_ReadCompare(void) 
    {
        #if(NeckHandle_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(NeckHandle_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(NeckHandle_COMPARE1_LSB_PTR));
        #endif /* (NeckHandle_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: NeckHandle_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 NeckHandle_ReadCompare1(void) 
    {
        return (CY_GET_REG16(NeckHandle_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: NeckHandle_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 NeckHandle_ReadCompare2(void) 
    {
        return (CY_GET_REG16(NeckHandle_COMPARE2_LSB_PTR));
    }

#endif /* (NeckHandle_UseOneCompareMode) */


/*******************************************************************************
* Function Name: NeckHandle_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 NeckHandle_ReadPeriod(void) 
{
    #if(NeckHandle_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(NeckHandle_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(NeckHandle_PERIOD_LSB_PTR));
    #endif /* (NeckHandle_UsingFixedFunction) */
}

#if ( NeckHandle_KillModeMinTime)


    /*******************************************************************************
    * Function Name: NeckHandle_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void NeckHandle_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(NeckHandle_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: NeckHandle_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 NeckHandle_ReadKillTime(void) 
    {
        return (CY_GET_REG8(NeckHandle_KILLMODEMINTIME_PTR));
    }

#endif /* ( NeckHandle_KillModeMinTime) */

/* [] END OF FILE */
