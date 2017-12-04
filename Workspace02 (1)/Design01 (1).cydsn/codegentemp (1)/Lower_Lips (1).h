/*******************************************************************************
* File Name: Lower_Lips.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Lower_Lips_H)
#define CY_PWM_Lower_Lips_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Lower_Lips_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Lower_Lips_Resolution                     (16u)
#define Lower_Lips_UsingFixedFunction             (0u)
#define Lower_Lips_DeadBandMode                   (0u)
#define Lower_Lips_KillModeMinTime                (0u)
#define Lower_Lips_KillMode                       (0u)
#define Lower_Lips_PWMMode                        (1u)
#define Lower_Lips_PWMModeIsCenterAligned         (0u)
#define Lower_Lips_DeadBandUsed                   (0u)
#define Lower_Lips_DeadBand2_4                    (0u)

#if !defined(Lower_Lips_PWMUDB_genblk8_stsreg__REMOVED)
    #define Lower_Lips_UseStatus                  (1u)
#else
    #define Lower_Lips_UseStatus                  (0u)
#endif /* !defined(Lower_Lips_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Lower_Lips_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Lower_Lips_UseControl                 (1u)
#else
    #define Lower_Lips_UseControl                 (0u)
#endif /* !defined(Lower_Lips_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Lower_Lips_UseOneCompareMode              (0u)
#define Lower_Lips_MinimumKillTime                (1u)
#define Lower_Lips_EnableMode                     (0u)

#define Lower_Lips_CompareMode1SW                 (0u)
#define Lower_Lips_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Lower_Lips__B_PWM__DISABLED 0
#define Lower_Lips__B_PWM__ASYNCHRONOUS 1
#define Lower_Lips__B_PWM__SINGLECYCLE 2
#define Lower_Lips__B_PWM__LATCHED 3
#define Lower_Lips__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Lower_Lips__B_PWM__DBMDISABLED 0
#define Lower_Lips__B_PWM__DBM_2_4_CLOCKS 1
#define Lower_Lips__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Lower_Lips__B_PWM__ONE_OUTPUT 0
#define Lower_Lips__B_PWM__TWO_OUTPUTS 1
#define Lower_Lips__B_PWM__DUAL_EDGE 2
#define Lower_Lips__B_PWM__CENTER_ALIGN 3
#define Lower_Lips__B_PWM__DITHER 5
#define Lower_Lips__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Lower_Lips__B_PWM__LESS_THAN 1
#define Lower_Lips__B_PWM__LESS_THAN_OR_EQUAL 2
#define Lower_Lips__B_PWM__GREATER_THAN 3
#define Lower_Lips__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Lower_Lips__B_PWM__EQUAL 0
#define Lower_Lips__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Lower_Lips_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Lower_Lips_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Lower_Lips_PWMModeIsCenterAligned) */
        #if (Lower_Lips_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Lower_Lips_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_256_CLOCKS || \
            Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Lower_Lips_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Lower_Lips_KillModeMinTime) */

        /* Backup control register */
        #if(Lower_Lips_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Lower_Lips_UseControl) */

    #endif /* (!Lower_Lips_UsingFixedFunction) */

}Lower_Lips_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Lower_Lips_Start(void) ;
void    Lower_Lips_Stop(void) ;

#if (Lower_Lips_UseStatus || Lower_Lips_UsingFixedFunction)
    void  Lower_Lips_SetInterruptMode(uint8 interruptMode) ;
    uint8 Lower_Lips_ReadStatusRegister(void) ;
#endif /* (Lower_Lips_UseStatus || Lower_Lips_UsingFixedFunction) */

#define Lower_Lips_GetInterruptSource() Lower_Lips_ReadStatusRegister()

#if (Lower_Lips_UseControl)
    uint8 Lower_Lips_ReadControlRegister(void) ;
    void  Lower_Lips_WriteControlRegister(uint8 control)
          ;
#endif /* (Lower_Lips_UseControl) */

#if (Lower_Lips_UseOneCompareMode)
   #if (Lower_Lips_CompareMode1SW)
       void    Lower_Lips_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Lower_Lips_CompareMode1SW) */
#else
    #if (Lower_Lips_CompareMode1SW)
        void    Lower_Lips_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Lower_Lips_CompareMode1SW) */
    #if (Lower_Lips_CompareMode2SW)
        void    Lower_Lips_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Lower_Lips_CompareMode2SW) */
#endif /* (Lower_Lips_UseOneCompareMode) */

#if (!Lower_Lips_UsingFixedFunction)
    uint16   Lower_Lips_ReadCounter(void) ;
    uint16 Lower_Lips_ReadCapture(void) ;

    #if (Lower_Lips_UseStatus)
            void Lower_Lips_ClearFIFO(void) ;
    #endif /* (Lower_Lips_UseStatus) */

    void    Lower_Lips_WriteCounter(uint16 counter)
            ;
#endif /* (!Lower_Lips_UsingFixedFunction) */

void    Lower_Lips_WritePeriod(uint16 period)
        ;
uint16 Lower_Lips_ReadPeriod(void) ;

#if (Lower_Lips_UseOneCompareMode)
    void    Lower_Lips_WriteCompare(uint16 compare)
            ;
    uint16 Lower_Lips_ReadCompare(void) ;
#else
    void    Lower_Lips_WriteCompare1(uint16 compare)
            ;
    uint16 Lower_Lips_ReadCompare1(void) ;
    void    Lower_Lips_WriteCompare2(uint16 compare)
            ;
    uint16 Lower_Lips_ReadCompare2(void) ;
#endif /* (Lower_Lips_UseOneCompareMode) */


#if (Lower_Lips_DeadBandUsed)
    void    Lower_Lips_WriteDeadTime(uint8 deadtime) ;
    uint8   Lower_Lips_ReadDeadTime(void) ;
#endif /* (Lower_Lips_DeadBandUsed) */

#if ( Lower_Lips_KillModeMinTime)
    void Lower_Lips_WriteKillTime(uint8 killtime) ;
    uint8 Lower_Lips_ReadKillTime(void) ;
#endif /* ( Lower_Lips_KillModeMinTime) */

void Lower_Lips_Init(void) ;
void Lower_Lips_Enable(void) ;
void Lower_Lips_Sleep(void) ;
void Lower_Lips_Wakeup(void) ;
void Lower_Lips_SaveConfig(void) ;
void Lower_Lips_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Lower_Lips_INIT_PERIOD_VALUE          (60000u)
#define Lower_Lips_INIT_COMPARE_VALUE1        (0u)
#define Lower_Lips_INIT_COMPARE_VALUE2        (0u)
#define Lower_Lips_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Lower_Lips_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lower_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lower_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lower_Lips_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Lower_Lips_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Lower_Lips_CTRL_CMPMODE2_SHIFT)
#define Lower_Lips_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Lower_Lips_CTRL_CMPMODE1_SHIFT)
#define Lower_Lips_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Lower_Lips_UsingFixedFunction)
   #define Lower_Lips_PERIOD_LSB              (*(reg16 *) Lower_Lips_PWMHW__PER0)
   #define Lower_Lips_PERIOD_LSB_PTR          ( (reg16 *) Lower_Lips_PWMHW__PER0)
   #define Lower_Lips_COMPARE1_LSB            (*(reg16 *) Lower_Lips_PWMHW__CNT_CMP0)
   #define Lower_Lips_COMPARE1_LSB_PTR        ( (reg16 *) Lower_Lips_PWMHW__CNT_CMP0)
   #define Lower_Lips_COMPARE2_LSB            (0x00u)
   #define Lower_Lips_COMPARE2_LSB_PTR        (0x00u)
   #define Lower_Lips_COUNTER_LSB             (*(reg16 *) Lower_Lips_PWMHW__CNT_CMP0)
   #define Lower_Lips_COUNTER_LSB_PTR         ( (reg16 *) Lower_Lips_PWMHW__CNT_CMP0)
   #define Lower_Lips_CAPTURE_LSB             (*(reg16 *) Lower_Lips_PWMHW__CAP0)
   #define Lower_Lips_CAPTURE_LSB_PTR         ( (reg16 *) Lower_Lips_PWMHW__CAP0)
   #define Lower_Lips_RT1                     (*(reg8 *)  Lower_Lips_PWMHW__RT1)
   #define Lower_Lips_RT1_PTR                 ( (reg8 *)  Lower_Lips_PWMHW__RT1)

#else
   #if (Lower_Lips_Resolution == 8u) /* 8bit - PWM */

       #if(Lower_Lips_PWMModeIsCenterAligned)
           #define Lower_Lips_PERIOD_LSB      (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Lower_Lips_PERIOD_LSB_PTR  ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Lower_Lips_PERIOD_LSB      (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Lower_Lips_PERIOD_LSB_PTR  ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Lower_Lips_PWMModeIsCenterAligned) */

       #define Lower_Lips_COMPARE1_LSB        (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lower_Lips_COMPARE1_LSB_PTR    ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lower_Lips_COMPARE2_LSB        (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lower_Lips_COMPARE2_LSB_PTR    ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lower_Lips_COUNTERCAP_LSB      (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lower_Lips_COUNTERCAP_LSB_PTR  ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lower_Lips_COUNTER_LSB         (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lower_Lips_COUNTER_LSB_PTR     ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lower_Lips_CAPTURE_LSB         (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Lower_Lips_CAPTURE_LSB_PTR     ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Lower_Lips_PWMModeIsCenterAligned)
               #define Lower_Lips_PERIOD_LSB      (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Lower_Lips_PERIOD_LSB_PTR  ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Lower_Lips_PERIOD_LSB      (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Lower_Lips_PERIOD_LSB_PTR  ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Lower_Lips_PWMModeIsCenterAligned) */

            #define Lower_Lips_COMPARE1_LSB       (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lower_Lips_COMPARE1_LSB_PTR   ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lower_Lips_COMPARE2_LSB       (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lower_Lips_COMPARE2_LSB_PTR   ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lower_Lips_COUNTERCAP_LSB     (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lower_Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lower_Lips_COUNTER_LSB        (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lower_Lips_COUNTER_LSB_PTR    ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lower_Lips_CAPTURE_LSB        (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Lower_Lips_CAPTURE_LSB_PTR    ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Lower_Lips_PWMModeIsCenterAligned)
               #define Lower_Lips_PERIOD_LSB      (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Lower_Lips_PERIOD_LSB_PTR  ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Lower_Lips_PERIOD_LSB      (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Lower_Lips_PERIOD_LSB_PTR  ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Lower_Lips_PWMModeIsCenterAligned) */

            #define Lower_Lips_COMPARE1_LSB       (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lower_Lips_COMPARE1_LSB_PTR   ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lower_Lips_COMPARE2_LSB       (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lower_Lips_COMPARE2_LSB_PTR   ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lower_Lips_COUNTERCAP_LSB     (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lower_Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lower_Lips_COUNTER_LSB        (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lower_Lips_COUNTER_LSB_PTR    ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lower_Lips_CAPTURE_LSB        (*(reg16 *) Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Lower_Lips_CAPTURE_LSB_PTR    ((reg16 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Lower_Lips_AUX_CONTROLDP1          (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Lower_Lips_AUX_CONTROLDP1_PTR      ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Lower_Lips_Resolution == 8) */

   #define Lower_Lips_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Lower_Lips_AUX_CONTROLDP0          (*(reg8 *)  Lower_Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Lower_Lips_AUX_CONTROLDP0_PTR      ((reg8 *)   Lower_Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Lower_Lips_UsingFixedFunction) */

#if(Lower_Lips_KillModeMinTime )
    #define Lower_Lips_KILLMODEMINTIME        (*(reg8 *)  Lower_Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Lower_Lips_KILLMODEMINTIME_PTR    ((reg8 *)   Lower_Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Lower_Lips_KillModeMinTime ) */

#if(Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_256_CLOCKS)
    #define Lower_Lips_DEADBAND_COUNT         (*(reg8 *)  Lower_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lower_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lower_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lower_Lips_DEADBAND_LSB_PTR       ((reg8 *)   Lower_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Lower_Lips_DEADBAND_LSB           (*(reg8 *)  Lower_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Lower_Lips_UsingFixedFunction)
        #define Lower_Lips_DEADBAND_COUNT         (*(reg8 *)  Lower_Lips_PWMHW__CFG0)
        #define Lower_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lower_Lips_PWMHW__CFG0)
        #define Lower_Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lower_Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Lower_Lips_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Lower_Lips_DEADBAND_COUNT         (*(reg8 *)  Lower_Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lower_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Lower_Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lower_Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lower_Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Lower_Lips_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Lower_Lips_UsingFixedFunction) */
#endif /* (Lower_Lips_DeadBandMode == Lower_Lips__B_PWM__DBM_256_CLOCKS) */



#if (Lower_Lips_UsingFixedFunction)
    #define Lower_Lips_STATUS                 (*(reg8 *) Lower_Lips_PWMHW__SR0)
    #define Lower_Lips_STATUS_PTR             ((reg8 *) Lower_Lips_PWMHW__SR0)
    #define Lower_Lips_STATUS_MASK            (*(reg8 *) Lower_Lips_PWMHW__SR0)
    #define Lower_Lips_STATUS_MASK_PTR        ((reg8 *) Lower_Lips_PWMHW__SR0)
    #define Lower_Lips_CONTROL                (*(reg8 *) Lower_Lips_PWMHW__CFG0)
    #define Lower_Lips_CONTROL_PTR            ((reg8 *) Lower_Lips_PWMHW__CFG0)
    #define Lower_Lips_CONTROL2               (*(reg8 *) Lower_Lips_PWMHW__CFG1)
    #define Lower_Lips_CONTROL3               (*(reg8 *) Lower_Lips_PWMHW__CFG2)
    #define Lower_Lips_GLOBAL_ENABLE          (*(reg8 *) Lower_Lips_PWMHW__PM_ACT_CFG)
    #define Lower_Lips_GLOBAL_ENABLE_PTR      ( (reg8 *) Lower_Lips_PWMHW__PM_ACT_CFG)
    #define Lower_Lips_GLOBAL_STBY_ENABLE     (*(reg8 *) Lower_Lips_PWMHW__PM_STBY_CFG)
    #define Lower_Lips_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Lower_Lips_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Lower_Lips_BLOCK_EN_MASK          (Lower_Lips_PWMHW__PM_ACT_MSK)
    #define Lower_Lips_BLOCK_STBY_EN_MASK     (Lower_Lips_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Lower_Lips_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Lower_Lips_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Lower_Lips_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Lower_Lips_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Lower_Lips_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Lower_Lips_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Lower_Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Lower_Lips_CTRL_ENABLE_SHIFT)
    #define Lower_Lips_CTRL_RESET             (uint8)((uint8)0x01u << Lower_Lips_CTRL_RESET_SHIFT)
    #define Lower_Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lower_Lips_CTRL_CMPMODE2_SHIFT)
    #define Lower_Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lower_Lips_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Lower_Lips_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Lower_Lips_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Lower_Lips_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Lower_Lips_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Lower_Lips_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Lower_Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Lower_Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Lower_Lips_STATUS_TC_SHIFT - 4u)
    #define Lower_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Lower_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lower_Lips_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Lower_Lips_STATUS_TC              (uint8)((uint8)0x01u << Lower_Lips_STATUS_TC_SHIFT)
    #define Lower_Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Lower_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Lower_Lips_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Lower_Lips_STATUS_TC >> 4u)
    #define Lower_Lips_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Lower_Lips_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Lower_Lips_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Lower_Lips_RT1_MASK              (uint8)((uint8)0x03u << Lower_Lips_RT1_SHIFT)
    #define Lower_Lips_SYNC                  (uint8)((uint8)0x03u << Lower_Lips_RT1_SHIFT)
    #define Lower_Lips_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Lower_Lips_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Lower_Lips_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Lower_Lips_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Lower_Lips_SYNCDSI_SHIFT)


#else
    #define Lower_Lips_STATUS                (*(reg8 *)   Lower_Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lower_Lips_STATUS_PTR            ((reg8 *)    Lower_Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lower_Lips_STATUS_MASK           (*(reg8 *)   Lower_Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lower_Lips_STATUS_MASK_PTR       ((reg8 *)    Lower_Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lower_Lips_STATUS_AUX_CTRL       (*(reg8 *)   Lower_Lips_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Lower_Lips_CONTROL               (*(reg8 *)   Lower_Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Lower_Lips_CONTROL_PTR           ((reg8 *)    Lower_Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Lower_Lips_CTRL_ENABLE_SHIFT      (0x07u)
    #define Lower_Lips_CTRL_RESET_SHIFT       (0x06u)
    #define Lower_Lips_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Lower_Lips_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Lower_Lips_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Lower_Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Lower_Lips_CTRL_ENABLE_SHIFT)
    #define Lower_Lips_CTRL_RESET             (uint8)((uint8)0x01u << Lower_Lips_CTRL_RESET_SHIFT)
    #define Lower_Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lower_Lips_CTRL_CMPMODE2_SHIFT)
    #define Lower_Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lower_Lips_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Lower_Lips_STATUS_KILL_SHIFT          (0x05u)
    #define Lower_Lips_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Lower_Lips_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Lower_Lips_STATUS_TC_SHIFT            (0x02u)
    #define Lower_Lips_STATUS_CMP2_SHIFT          (0x01u)
    #define Lower_Lips_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Lower_Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (Lower_Lips_STATUS_KILL_SHIFT)
    #define Lower_Lips_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Lower_Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Lower_Lips_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Lower_Lips_STATUS_FIFOFULL_SHIFT)
    #define Lower_Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Lower_Lips_STATUS_TC_SHIFT)
    #define Lower_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (Lower_Lips_STATUS_CMP2_SHIFT)
    #define Lower_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lower_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Lower_Lips_STATUS_KILL            (uint8)((uint8)0x00u << Lower_Lips_STATUS_KILL_SHIFT )
    #define Lower_Lips_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Lower_Lips_STATUS_FIFOFULL_SHIFT)
    #define Lower_Lips_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Lower_Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Lower_Lips_STATUS_TC              (uint8)((uint8)0x01u << Lower_Lips_STATUS_TC_SHIFT)
    #define Lower_Lips_STATUS_CMP2            (uint8)((uint8)0x01u << Lower_Lips_STATUS_CMP2_SHIFT)
    #define Lower_Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Lower_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Lower_Lips_STATUS_KILL_INT_EN_MASK            (Lower_Lips_STATUS_KILL)
    #define Lower_Lips_STATUS_FIFOFULL_INT_EN_MASK        (Lower_Lips_STATUS_FIFOFULL)
    #define Lower_Lips_STATUS_FIFONEMPTY_INT_EN_MASK      (Lower_Lips_STATUS_FIFONEMPTY)
    #define Lower_Lips_STATUS_TC_INT_EN_MASK              (Lower_Lips_STATUS_TC)
    #define Lower_Lips_STATUS_CMP2_INT_EN_MASK            (Lower_Lips_STATUS_CMP2)
    #define Lower_Lips_STATUS_CMP1_INT_EN_MASK            (Lower_Lips_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Lower_Lips_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Lower_Lips_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Lower_Lips_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Lower_Lips_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Lower_Lips_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Lower_Lips_UsingFixedFunction */

#endif  /* CY_PWM_Lower_Lips_H */


/* [] END OF FILE */
