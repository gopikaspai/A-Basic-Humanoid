/*******************************************************************************
* File Name: Eye_Rod_PM.c
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

#include "Eye_Rod.h"

static Eye_Rod_backupStruct Eye_Rod_backup;


/*******************************************************************************
* Function Name: Eye_Rod_SaveConfig
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
*  Eye_Rod_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Eye_Rod_SaveConfig(void) 
{

    #if(!Eye_Rod_UsingFixedFunction)
        #if(!Eye_Rod_PWMModeIsCenterAligned)
            Eye_Rod_backup.PWMPeriod = Eye_Rod_ReadPeriod();
        #endif /* (!Eye_Rod_PWMModeIsCenterAligned) */
        Eye_Rod_backup.PWMUdb = Eye_Rod_ReadCounter();
        #if (Eye_Rod_UseStatus)
            Eye_Rod_backup.InterruptMaskValue = Eye_Rod_STATUS_MASK;
        #endif /* (Eye_Rod_UseStatus) */

        #if(Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_256_CLOCKS || \
            Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_2_4_CLOCKS)
            Eye_Rod_backup.PWMdeadBandValue = Eye_Rod_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Eye_Rod_KillModeMinTime)
             Eye_Rod_backup.PWMKillCounterPeriod = Eye_Rod_ReadKillTime();
        #endif /* (Eye_Rod_KillModeMinTime) */

        #if(Eye_Rod_UseControl)
            Eye_Rod_backup.PWMControlRegister = Eye_Rod_ReadControlRegister();
        #endif /* (Eye_Rod_UseControl) */
    #endif  /* (!Eye_Rod_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Eye_Rod_RestoreConfig
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
*  Eye_Rod_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Eye_Rod_RestoreConfig(void) 
{
        #if(!Eye_Rod_UsingFixedFunction)
            #if(!Eye_Rod_PWMModeIsCenterAligned)
                Eye_Rod_WritePeriod(Eye_Rod_backup.PWMPeriod);
            #endif /* (!Eye_Rod_PWMModeIsCenterAligned) */

            Eye_Rod_WriteCounter(Eye_Rod_backup.PWMUdb);

            #if (Eye_Rod_UseStatus)
                Eye_Rod_STATUS_MASK = Eye_Rod_backup.InterruptMaskValue;
            #endif /* (Eye_Rod_UseStatus) */

            #if(Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_256_CLOCKS || \
                Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_2_4_CLOCKS)
                Eye_Rod_WriteDeadTime(Eye_Rod_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Eye_Rod_KillModeMinTime)
                Eye_Rod_WriteKillTime(Eye_Rod_backup.PWMKillCounterPeriod);
            #endif /* (Eye_Rod_KillModeMinTime) */

            #if(Eye_Rod_UseControl)
                Eye_Rod_WriteControlRegister(Eye_Rod_backup.PWMControlRegister);
            #endif /* (Eye_Rod_UseControl) */
        #endif  /* (!Eye_Rod_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Eye_Rod_Sleep
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
*  Eye_Rod_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Eye_Rod_Sleep(void) 
{
    #if(Eye_Rod_UseControl)
        if(Eye_Rod_CTRL_ENABLE == (Eye_Rod_CONTROL & Eye_Rod_CTRL_ENABLE))
        {
            /*Component is enabled */
            Eye_Rod_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Eye_Rod_backup.PWMEnableState = 0u;
        }
    #endif /* (Eye_Rod_UseControl) */

    /* Stop component */
    Eye_Rod_Stop();

    /* Save registers configuration */
    Eye_Rod_SaveConfig();
}


/*******************************************************************************
* Function Name: Eye_Rod_Wakeup
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
*  Eye_Rod_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Eye_Rod_Wakeup(void) 
{
     /* Restore registers values */
    Eye_Rod_RestoreConfig();

    if(Eye_Rod_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Eye_Rod_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
