/*******************************************************************************
* File Name: Lower_Lips_PM.c
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

#include "Lower_Lips.h"

static Lower_Lips_backupStruct Lower_Lips_backup;


/*******************************************************************************
* Function Name: Lower_Lips_SaveConfig
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
*  Lower_Lips_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Lower_Lips_SaveConfig(void) 
{

    #if(!Lower_Lips_UsingFixedFunction)
        #if(!Lower_Lips_PWMModeIsCenterAligned)
            Lower_Lips_backup.PWMPeriod = Lower_Lips_ReadPeriod();
        #endif /* (!Lower_Lips_PWMModeIsCenterAligned) */
        Lower_Lips_backup.PWMUdb = Lower_Lips_ReadCounter();
        #if (Lower_Lips_UseStatus)
            Lower_Lips_backup.InterruptMaskValue = Lower_Lips_STATUS_MASK;
        #endif /* (Lower_Lips_UseStatus) */

        #if(Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_256_CLOCKS || \
            Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_2_4_CLOCKS)
            Lower_Lips_backup.PWMdeadBandValue = Lower_Lips_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Lower_Lips_KillModeMinTime)
             Lower_Lips_backup.PWMKillCounterPeriod = Lower_Lips_ReadKillTime();
        #endif /* (Lower_Lips_KillModeMinTime) */

        #if(Lower_Lips_UseControl)
            Lower_Lips_backup.PWMControlRegister = Lower_Lips_ReadControlRegister();
        #endif /* (Lower_Lips_UseControl) */
    #endif  /* (!Lower_Lips_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lower_Lips_RestoreConfig
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
*  Lower_Lips_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Lower_Lips_RestoreConfig(void) 
{
        #if(!Lower_Lips_UsingFixedFunction)
            #if(!Lower_Lips_PWMModeIsCenterAligned)
                Lower_Lips_WritePeriod(Lower_Lips_backup.PWMPeriod);
            #endif /* (!Lower_Lips_PWMModeIsCenterAligned) */

            Lower_Lips_WriteCounter(Lower_Lips_backup.PWMUdb);

            #if (Lower_Lips_UseStatus)
                Lower_Lips_STATUS_MASK = Lower_Lips_backup.InterruptMaskValue;
            #endif /* (Lower_Lips_UseStatus) */

            #if(Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_256_CLOCKS || \
                Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_2_4_CLOCKS)
                Lower_Lips_WriteDeadTime(Lower_Lips_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Lower_Lips_KillModeMinTime)
                Lower_Lips_WriteKillTime(Lower_Lips_backup.PWMKillCounterPeriod);
            #endif /* (Lower_Lips_KillModeMinTime) */

            #if(Lower_Lips_UseControl)
                Lower_Lips_WriteControlRegister(Lower_Lips_backup.PWMControlRegister);
            #endif /* (Lower_Lips_UseControl) */
        #endif  /* (!Lower_Lips_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Lower_Lips_Sleep
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
*  Lower_Lips_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Lower_Lips_Sleep(void) 
{
    #if(Lower_Lips_UseControl)
        if(Lower_Lips_CTRL_ENABLE == (Lower_Lips_CONTROL & Lower_Lips_CTRL_ENABLE))
        {
            /*Component is enabled */
            Lower_Lips_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Lower_Lips_backup.PWMEnableState = 0u;
        }
    #endif /* (Lower_Lips_UseControl) */

    /* Stop component */
    Lower_Lips_Stop();

    /* Save registers configuration */
    Lower_Lips_SaveConfig();
}


/*******************************************************************************
* Function Name: Lower_Lips_Wakeup
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
*  Lower_Lips_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Lower_Lips_Wakeup(void) 
{
     /* Restore registers values */
    Lower_Lips_RestoreConfig();

    if(Lower_Lips_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Lower_Lips_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
