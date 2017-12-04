/*******************************************************************************
* File Name: Upper_Lips_PM.c
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

#include "Upper_Lips.h"

static Upper_Lips_backupStruct Upper_Lips_backup;


/*******************************************************************************
* Function Name: Upper_Lips_SaveConfig
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
*  Upper_Lips_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Upper_Lips_SaveConfig(void) 
{

    #if(!Upper_Lips_UsingFixedFunction)
        #if(!Upper_Lips_PWMModeIsCenterAligned)
            Upper_Lips_backup.PWMPeriod = Upper_Lips_ReadPeriod();
        #endif /* (!Upper_Lips_PWMModeIsCenterAligned) */
        Upper_Lips_backup.PWMUdb = Upper_Lips_ReadCounter();
        #if (Upper_Lips_UseStatus)
            Upper_Lips_backup.InterruptMaskValue = Upper_Lips_STATUS_MASK;
        #endif /* (Upper_Lips_UseStatus) */

        #if(Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_256_CLOCKS || \
            Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_2_4_CLOCKS)
            Upper_Lips_backup.PWMdeadBandValue = Upper_Lips_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Upper_Lips_KillModeMinTime)
             Upper_Lips_backup.PWMKillCounterPeriod = Upper_Lips_ReadKillTime();
        #endif /* (Upper_Lips_KillModeMinTime) */

        #if(Upper_Lips_UseControl)
            Upper_Lips_backup.PWMControlRegister = Upper_Lips_ReadControlRegister();
        #endif /* (Upper_Lips_UseControl) */
    #endif  /* (!Upper_Lips_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Upper_Lips_RestoreConfig
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
*  Upper_Lips_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Upper_Lips_RestoreConfig(void) 
{
        #if(!Upper_Lips_UsingFixedFunction)
            #if(!Upper_Lips_PWMModeIsCenterAligned)
                Upper_Lips_WritePeriod(Upper_Lips_backup.PWMPeriod);
            #endif /* (!Upper_Lips_PWMModeIsCenterAligned) */

            Upper_Lips_WriteCounter(Upper_Lips_backup.PWMUdb);

            #if (Upper_Lips_UseStatus)
                Upper_Lips_STATUS_MASK = Upper_Lips_backup.InterruptMaskValue;
            #endif /* (Upper_Lips_UseStatus) */

            #if(Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_256_CLOCKS || \
                Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_2_4_CLOCKS)
                Upper_Lips_WriteDeadTime(Upper_Lips_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Upper_Lips_KillModeMinTime)
                Upper_Lips_WriteKillTime(Upper_Lips_backup.PWMKillCounterPeriod);
            #endif /* (Upper_Lips_KillModeMinTime) */

            #if(Upper_Lips_UseControl)
                Upper_Lips_WriteControlRegister(Upper_Lips_backup.PWMControlRegister);
            #endif /* (Upper_Lips_UseControl) */
        #endif  /* (!Upper_Lips_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Upper_Lips_Sleep
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
*  Upper_Lips_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Upper_Lips_Sleep(void) 
{
    #if(Upper_Lips_UseControl)
        if(Upper_Lips_CTRL_ENABLE == (Upper_Lips_CONTROL & Upper_Lips_CTRL_ENABLE))
        {
            /*Component is enabled */
            Upper_Lips_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Upper_Lips_backup.PWMEnableState = 0u;
        }
    #endif /* (Upper_Lips_UseControl) */

    /* Stop component */
    Upper_Lips_Stop();

    /* Save registers configuration */
    Upper_Lips_SaveConfig();
}


/*******************************************************************************
* Function Name: Upper_Lips_Wakeup
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
*  Upper_Lips_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Upper_Lips_Wakeup(void) 
{
     /* Restore registers values */
    Upper_Lips_RestoreConfig();

    if(Upper_Lips_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Upper_Lips_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
