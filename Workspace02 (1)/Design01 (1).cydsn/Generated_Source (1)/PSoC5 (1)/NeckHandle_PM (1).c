/*******************************************************************************
* File Name: NeckHandle_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "NeckHandle.h"

static NeckHandle_backupStruct NeckHandle_backup;


/*******************************************************************************
* Function Name: NeckHandle_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NeckHandle_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void NeckHandle_SaveConfig(void) 
{

    #if(!NeckHandle_UsingFixedFunction)
        #if(!NeckHandle_PWMModeIsCenterAligned)
            NeckHandle_backup.PWMPeriod = NeckHandle_ReadPeriod();
        #endif /* (!NeckHandle_PWMModeIsCenterAligned) */
        NeckHandle_backup.PWMUdb = NeckHandle_ReadCounter();
        #if (NeckHandle_UseStatus)
            NeckHandle_backup.InterruptMaskValue = NeckHandle_STATUS_MASK;
        #endif /* (NeckHandle_UseStatus) */

        #if(NeckHandle_DeadBandMode == NeckHandle__B_PWM__DBM_256_CLOCKS || \
            NeckHandle_DeadBandMode == NeckHandle__B_PWM__DBM_2_4_CLOCKS)
            NeckHandle_backup.PWMdeadBandValue = NeckHandle_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(NeckHandle_KillModeMinTime)
             NeckHandle_backup.PWMKillCounterPeriod = NeckHandle_ReadKillTime();
        #endif /* (NeckHandle_KillModeMinTime) */

        #if(NeckHandle_UseControl)
            NeckHandle_backup.PWMControlRegister = NeckHandle_ReadControlRegister();
        #endif /* (NeckHandle_UseControl) */
    #endif  /* (!NeckHandle_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: NeckHandle_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NeckHandle_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void NeckHandle_RestoreConfig(void) 
{
        #if(!NeckHandle_UsingFixedFunction)
            #if(!NeckHandle_PWMModeIsCenterAligned)
                NeckHandle_WritePeriod(NeckHandle_backup.PWMPeriod);
            #endif /* (!NeckHandle_PWMModeIsCenterAligned) */

            NeckHandle_WriteCounter(NeckHandle_backup.PWMUdb);

            #if (NeckHandle_UseStatus)
                NeckHandle_STATUS_MASK = NeckHandle_backup.InterruptMaskValue;
            #endif /* (NeckHandle_UseStatus) */

            #if(NeckHandle_DeadBandMode == NeckHandle__B_PWM__DBM_256_CLOCKS || \
                NeckHandle_DeadBandMode == NeckHandle__B_PWM__DBM_2_4_CLOCKS)
                NeckHandle_WriteDeadTime(NeckHandle_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(NeckHandle_KillModeMinTime)
                NeckHandle_WriteKillTime(NeckHandle_backup.PWMKillCounterPeriod);
            #endif /* (NeckHandle_KillModeMinTime) */

            #if(NeckHandle_UseControl)
                NeckHandle_WriteControlRegister(NeckHandle_backup.PWMControlRegister);
            #endif /* (NeckHandle_UseControl) */
        #endif  /* (!NeckHandle_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: NeckHandle_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NeckHandle_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void NeckHandle_Sleep(void) 
{
    #if(NeckHandle_UseControl)
        if(NeckHandle_CTRL_ENABLE == (NeckHandle_CONTROL & NeckHandle_CTRL_ENABLE))
        {
            /*Component is enabled */
            NeckHandle_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            NeckHandle_backup.PWMEnableState = 0u;
        }
    #endif /* (NeckHandle_UseControl) */

    /* Stop component */
    NeckHandle_Stop();

    /* Save registers configuration */
    NeckHandle_SaveConfig();
}


/*******************************************************************************
* Function Name: NeckHandle_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  NeckHandle_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void NeckHandle_Wakeup(void) 
{
     /* Restore registers values */
    NeckHandle_RestoreConfig();

    if(NeckHandle_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        NeckHandle_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
