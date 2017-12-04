/*******************************************************************************
* File Name: Upper_Lips.h
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

#if !defined(CY_PWM_Upper_Lips_H)
#define CY_PWM_Upper_Lips_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Upper_Lips_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Upper_Lips_Resolution                     (16u)
#define Upper_Lips_UsingFixedFunction             (0u)
#define Upper_Lips_DeadBandMode                   (0u)
#define Upper_Lips_KillModeMinTime                (0u)
#define Upper_Lips_KillMode                       (0u)
#define Upper_Lips_PWMMode                        (1u)
#define Upper_Lips_PWMModeIsCenterAligned         (0u)
#define Upper_Lips_DeadBandUsed                   (0u)
#define Upper_Lips_DeadBand2_4                    (0u)

#if !defined(Upper_Lips_PWMUDB_genblk8_stsreg__REMOVED)
    #define Upper_Lips_UseStatus                  (1u)
#else
    #define Upper_Lips_UseStatus                  (0u)
#endif /* !defined(Upper_Lips_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Upper_Lips_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Upper_Lips_UseControl                 (1u)
#else
    #define Upper_Lips_UseControl                 (0u)
#endif /* !defined(Upper_Lips_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Upper_Lips_UseOneCompareMode              (0u)
#define Upper_Lips_MinimumKillTime                (1u)
#define Upper_Lips_EnableMode                     (0u)

#define Upper_Lips_CompareMode1SW                 (0u)
#define Upper_Lips_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Upper_Lips__B_PWM__DISABLED 0
#define Upper_Lips__B_PWM__ASYNCHRONOUS 1
#define Upper_Lips__B_PWM__SINGLECYCLE 2
#define Upper_Lips__B_PWM__LATCHED 3
#define Upper_Lips__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Upper_Lips__B_PWM__DBMDISABLED 0
#define Upper_Lips__B_PWM__DBM_2_4_CLOCKS 1
#define Upper_Lips__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Upper_Lips__B_PWM__ONE_OUTPUT 0
#define Upper_Lips__B_PWM__TWO_OUTPUTS 1
#define Upper_Lips__B_PWM__DUAL_EDGE 2
#define Upper_Lips__B_PWM__CENTER_ALIGN 3
#define Upper_Lips__B_PWM__DITHER 5
#define Upper_Lips__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Upper_Lips__B_PWM__LESS_THAN 1
#define Upper_Lips__B_PWM__LESS_THAN_OR_EQUAL 2
#define Upper_Lips__B_PWM__GREATER_THAN 3
#define Upper_Lips__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Upper_Lips__B_PWM__EQUAL 0
#define Upper_Lips__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Upper_Lips_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Upper_Lips_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Upper_Lips_PWMModeIsCenterAligned) */
        #if (Upper_Lips_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Upper_Lips_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_256_CLOCKS || \
            Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Upper_Lips_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Upper_Lips_KillModeMinTime) */

        /* Backup control register */
        #if(Upper_Lips_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Upper_Lips_UseControl) */

    #endif /* (!Upper_Lips_UsingFixedFunction) */

}Upper_Lips_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Upper_Lips_Start(void) ;
void    Upper_Lips_Stop(void) ;

#if (Upper_Lips_UseStatus || Upper_Lips_UsingFixedFunction)
    void  Upper_Lips_SetInterruptMode(uint8 interruptMode) ;
    uint8 Upper_Lips_ReadStatusRegister(void) ;
#endif /* (Upper_Lips_UseStatus || Upper_Lips_UsingFixedFunction) */

#define Upper_Lips_GetInterruptSource() Upper_Lips_ReadStatusRegister()

#if (Upper_Lips_UseControl)
    uint8 Upper_Lips_ReadControlRegister(void) ;
    void  Upper_Lips_WriteControlRegister(uint8 control)
          ;
#endif /* (Upper_Lips_UseControl) */

#if (Upper_Lips_UseOneCompareMode)
   #if (Upper_Lips_CompareMode1SW)
       void    Upper_Lips_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Upper_Lips_CompareMode1SW) */
#else
    #if (Upper_Lips_CompareMode1SW)
        void    Upper_Lips_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Upper_Lips_CompareMode1SW) */
    #if (Upper_Lips_CompareMode2SW)
        void    Upper_Lips_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Upper_Lips_CompareMode2SW) */
#endif /* (Upper_Lips_UseOneCompareMode) */

#if (!Upper_Lips_UsingFixedFunction)
    uint16   Upper_Lips_ReadCounter(void) ;
    uint16 Upper_Lips_ReadCapture(void) ;

    #if (Upper_Lips_UseStatus)
            void Upper_Lips_ClearFIFO(void) ;
    #endif /* (Upper_Lips_UseStatus) */

    void    Upper_Lips_WriteCounter(uint16 counter)
            ;
#endif /* (!Upper_Lips_UsingFixedFunction) */

void    Upper_Lips_WritePeriod(uint16 period)
        ;
uint16 Upper_Lips_ReadPeriod(void) ;

#if (Upper_Lips_UseOneCompareMode)
    void    Upper_Lips_WriteCompare(uint16 compare)
            ;
    uint16 Upper_Lips_ReadCompare(void) ;
#else
    void    Upper_Lips_WriteCompare1(uint16 compare)
            ;
    uint16 Upper_Lips_ReadCompare1(void) ;
    void    Upper_Lips_WriteCompare2(uint16 compare)
            ;
    uint16 Upper_Lips_ReadCompare2(void) ;
#endif /* (Upper_Lips_UseOneCompareMode) */


#if (Upper_Lips_DeadBandUsed)
    void    Upper_Lips_WriteDeadTime(uint8 deadtime) ;
    uint8   Upper_Lips_ReadDeadTime(void) ;
#endif /* (Upper_Lips_DeadBandUsed) */

#if ( Upper_Lips_KillModeMinTime)
    void Upper_Lips_WriteKillTime(uint8 killtime) ;
    uint8 Upper_Lips_ReadKillTime(void) ;
#endif /* ( Upper_Lips_KillModeMinTime) */

void Upper_Lips_Init(void) ;
void Upper_Lips_Enable(void) ;
void Upper_Lips_Sleep(void) ;
void Upper_Lips_Wakeup(void) ;
void Upper_Lips_SaveConfig(void) ;
void Upper_Lips_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Upper_Lips_INIT_PERIOD_VALUE          (60000u)
#define Upper_Lips_INIT_COMPARE_VALUE1        (0u)
#define Upper_Lips_INIT_COMPARE_VALUE2        (0u)
#define Upper_Lips_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Upper_Lips_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Upper_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Upper_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Upper_Lips_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Upper_Lips_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Upper_Lips_CTRL_CMPMODE2_SHIFT)
#define Upper_Lips_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Upper_Lips_CTRL_CMPMODE1_SHIFT)
#define Upper_Lips_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Upper_Lips_UsingFixedFunction)
   #define Upper_Lips_PERIOD_LSB              (*(reg16 *) Upper_Lips_PWMHW__PER0)
   #define Upper_Lips_PERIOD_LSB_PTR          ( (reg16 *) Upper_Lips_PWMHW__PER0)
   #define Upper_Lips_COMPARE1_LSB            (*(reg16 *) Upper_Lips_PWMHW__CNT_CMP0)
   #define Upper_Lips_COMPARE1_LSB_PTR        ( (reg16 *) Upper_Lips_PWMHW__CNT_CMP0)
   #define Upper_Lips_COMPARE2_LSB            (0x00u)
   #define Upper_Lips_COMPARE2_LSB_PTR        (0x00u)
   #define Upper_Lips_COUNTER_LSB             (*(reg16 *) Upper_Lips_PWMHW__CNT_CMP0)
   #define Upper_Lips_COUNTER_LSB_PTR         ( (reg16 *) Upper_Lips_PWMHW__CNT_CMP0)
   #define Upper_Lips_CAPTURE_LSB             (*(reg16 *) Upper_Lips_PWMHW__CAP0)
   #define Upper_Lips_CAPTURE_LSB_PTR         ( (reg16 *) Upper_Lips_PWMHW__CAP0)
   #define Upper_Lips_RT1                     (*(reg8 *)  Upper_Lips_PWMHW__RT1)
   #define Upper_Lips_RT1_PTR                 ( (reg8 *)  Upper_Lips_PWMHW__RT1)

#else
   #if (Upper_Lips_Resolution == 8u) /* 8bit - PWM */

       #if(Upper_Lips_PWMModeIsCenterAligned)
           #define Upper_Lips_PERIOD_LSB      (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Upper_Lips_PERIOD_LSB_PTR  ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Upper_Lips_PERIOD_LSB      (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Upper_Lips_PERIOD_LSB_PTR  ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Upper_Lips_PWMModeIsCenterAligned) */

       #define Upper_Lips_COMPARE1_LSB        (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Upper_Lips_COMPARE1_LSB_PTR    ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Upper_Lips_COMPARE2_LSB        (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Upper_Lips_COMPARE2_LSB_PTR    ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Upper_Lips_COUNTERCAP_LSB      (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Upper_Lips_COUNTERCAP_LSB_PTR  ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Upper_Lips_COUNTER_LSB         (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Upper_Lips_COUNTER_LSB_PTR     ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Upper_Lips_CAPTURE_LSB         (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Upper_Lips_CAPTURE_LSB_PTR     ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Upper_Lips_PWMModeIsCenterAligned)
               #define Upper_Lips_PERIOD_LSB      (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Upper_Lips_PERIOD_LSB_PTR  ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Upper_Lips_PERIOD_LSB      (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Upper_Lips_PERIOD_LSB_PTR  ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Upper_Lips_PWMModeIsCenterAligned) */

            #define Upper_Lips_COMPARE1_LSB       (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Upper_Lips_COMPARE1_LSB_PTR   ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Upper_Lips_COMPARE2_LSB       (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Upper_Lips_COMPARE2_LSB_PTR   ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Upper_Lips_COUNTERCAP_LSB     (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Upper_Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Upper_Lips_COUNTER_LSB        (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Upper_Lips_COUNTER_LSB_PTR    ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Upper_Lips_CAPTURE_LSB        (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Upper_Lips_CAPTURE_LSB_PTR    ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Upper_Lips_PWMModeIsCenterAligned)
               #define Upper_Lips_PERIOD_LSB      (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Upper_Lips_PERIOD_LSB_PTR  ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Upper_Lips_PERIOD_LSB      (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Upper_Lips_PERIOD_LSB_PTR  ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Upper_Lips_PWMModeIsCenterAligned) */

            #define Upper_Lips_COMPARE1_LSB       (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Upper_Lips_COMPARE1_LSB_PTR   ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Upper_Lips_COMPARE2_LSB       (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Upper_Lips_COMPARE2_LSB_PTR   ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Upper_Lips_COUNTERCAP_LSB     (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Upper_Lips_COUNTERCAP_LSB_PTR ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Upper_Lips_COUNTER_LSB        (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Upper_Lips_COUNTER_LSB_PTR    ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Upper_Lips_CAPTURE_LSB        (*(reg16 *) Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Upper_Lips_CAPTURE_LSB_PTR    ((reg16 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Upper_Lips_AUX_CONTROLDP1          (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Upper_Lips_AUX_CONTROLDP1_PTR      ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Upper_Lips_Resolution == 8) */

   #define Upper_Lips_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Upper_Lips_AUX_CONTROLDP0          (*(reg8 *)  Upper_Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Upper_Lips_AUX_CONTROLDP0_PTR      ((reg8 *)   Upper_Lips_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Upper_Lips_UsingFixedFunction) */

#if(Upper_Lips_KillModeMinTime )
    #define Upper_Lips_KILLMODEMINTIME        (*(reg8 *)  Upper_Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Upper_Lips_KILLMODEMINTIME_PTR    ((reg8 *)   Upper_Lips_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Upper_Lips_KillModeMinTime ) */

#if(Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_256_CLOCKS)
    #define Upper_Lips_DEADBAND_COUNT         (*(reg8 *)  Upper_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Upper_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Upper_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Upper_Lips_DEADBAND_LSB_PTR       ((reg8 *)   Upper_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Upper_Lips_DEADBAND_LSB           (*(reg8 *)  Upper_Lips_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Upper_Lips_UsingFixedFunction)
        #define Upper_Lips_DEADBAND_COUNT         (*(reg8 *)  Upper_Lips_PWMHW__CFG0)
        #define Upper_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Upper_Lips_PWMHW__CFG0)
        #define Upper_Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Upper_Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Upper_Lips_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Upper_Lips_DEADBAND_COUNT         (*(reg8 *)  Upper_Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Upper_Lips_DEADBAND_COUNT_PTR     ((reg8 *)   Upper_Lips_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Upper_Lips_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Upper_Lips_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Upper_Lips_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Upper_Lips_UsingFixedFunction) */
#endif /* (Upper_Lips_DeadBandMode == Upper_Lips__B_PWM__DBM_256_CLOCKS) */



#if (Upper_Lips_UsingFixedFunction)
    #define Upper_Lips_STATUS                 (*(reg8 *) Upper_Lips_PWMHW__SR0)
    #define Upper_Lips_STATUS_PTR             ((reg8 *) Upper_Lips_PWMHW__SR0)
    #define Upper_Lips_STATUS_MASK            (*(reg8 *) Upper_Lips_PWMHW__SR0)
    #define Upper_Lips_STATUS_MASK_PTR        ((reg8 *) Upper_Lips_PWMHW__SR0)
    #define Upper_Lips_CONTROL                (*(reg8 *) Upper_Lips_PWMHW__CFG0)
    #define Upper_Lips_CONTROL_PTR            ((reg8 *) Upper_Lips_PWMHW__CFG0)
    #define Upper_Lips_CONTROL2               (*(reg8 *) Upper_Lips_PWMHW__CFG1)
    #define Upper_Lips_CONTROL3               (*(reg8 *) Upper_Lips_PWMHW__CFG2)
    #define Upper_Lips_GLOBAL_ENABLE          (*(reg8 *) Upper_Lips_PWMHW__PM_ACT_CFG)
    #define Upper_Lips_GLOBAL_ENABLE_PTR      ( (reg8 *) Upper_Lips_PWMHW__PM_ACT_CFG)
    #define Upper_Lips_GLOBAL_STBY_ENABLE     (*(reg8 *) Upper_Lips_PWMHW__PM_STBY_CFG)
    #define Upper_Lips_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Upper_Lips_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Upper_Lips_BLOCK_EN_MASK          (Upper_Lips_PWMHW__PM_ACT_MSK)
    #define Upper_Lips_BLOCK_STBY_EN_MASK     (Upper_Lips_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Upper_Lips_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Upper_Lips_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Upper_Lips_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Upper_Lips_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Upper_Lips_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Upper_Lips_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Upper_Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Upper_Lips_CTRL_ENABLE_SHIFT)
    #define Upper_Lips_CTRL_RESET             (uint8)((uint8)0x01u << Upper_Lips_CTRL_RESET_SHIFT)
    #define Upper_Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Upper_Lips_CTRL_CMPMODE2_SHIFT)
    #define Upper_Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Upper_Lips_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Upper_Lips_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Upper_Lips_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Upper_Lips_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Upper_Lips_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Upper_Lips_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Upper_Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Upper_Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Upper_Lips_STATUS_TC_SHIFT - 4u)
    #define Upper_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Upper_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Upper_Lips_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Upper_Lips_STATUS_TC              (uint8)((uint8)0x01u << Upper_Lips_STATUS_TC_SHIFT)
    #define Upper_Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Upper_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Upper_Lips_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Upper_Lips_STATUS_TC >> 4u)
    #define Upper_Lips_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Upper_Lips_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Upper_Lips_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Upper_Lips_RT1_MASK              (uint8)((uint8)0x03u << Upper_Lips_RT1_SHIFT)
    #define Upper_Lips_SYNC                  (uint8)((uint8)0x03u << Upper_Lips_RT1_SHIFT)
    #define Upper_Lips_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Upper_Lips_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Upper_Lips_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Upper_Lips_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Upper_Lips_SYNCDSI_SHIFT)


#else
    #define Upper_Lips_STATUS                (*(reg8 *)   Upper_Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Upper_Lips_STATUS_PTR            ((reg8 *)    Upper_Lips_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Upper_Lips_STATUS_MASK           (*(reg8 *)   Upper_Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Upper_Lips_STATUS_MASK_PTR       ((reg8 *)    Upper_Lips_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Upper_Lips_STATUS_AUX_CTRL       (*(reg8 *)   Upper_Lips_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Upper_Lips_CONTROL               (*(reg8 *)   Upper_Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Upper_Lips_CONTROL_PTR           ((reg8 *)    Upper_Lips_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Upper_Lips_CTRL_ENABLE_SHIFT      (0x07u)
    #define Upper_Lips_CTRL_RESET_SHIFT       (0x06u)
    #define Upper_Lips_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Upper_Lips_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Upper_Lips_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Upper_Lips_CTRL_ENABLE            (uint8)((uint8)0x01u << Upper_Lips_CTRL_ENABLE_SHIFT)
    #define Upper_Lips_CTRL_RESET             (uint8)((uint8)0x01u << Upper_Lips_CTRL_RESET_SHIFT)
    #define Upper_Lips_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Upper_Lips_CTRL_CMPMODE2_SHIFT)
    #define Upper_Lips_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Upper_Lips_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Upper_Lips_STATUS_KILL_SHIFT          (0x05u)
    #define Upper_Lips_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Upper_Lips_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Upper_Lips_STATUS_TC_SHIFT            (0x02u)
    #define Upper_Lips_STATUS_CMP2_SHIFT          (0x01u)
    #define Upper_Lips_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Upper_Lips_STATUS_KILL_INT_EN_MASK_SHIFT          (Upper_Lips_STATUS_KILL_SHIFT)
    #define Upper_Lips_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Upper_Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Upper_Lips_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Upper_Lips_STATUS_FIFOFULL_SHIFT)
    #define Upper_Lips_STATUS_TC_INT_EN_MASK_SHIFT            (Upper_Lips_STATUS_TC_SHIFT)
    #define Upper_Lips_STATUS_CMP2_INT_EN_MASK_SHIFT          (Upper_Lips_STATUS_CMP2_SHIFT)
    #define Upper_Lips_STATUS_CMP1_INT_EN_MASK_SHIFT          (Upper_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Upper_Lips_STATUS_KILL            (uint8)((uint8)0x00u << Upper_Lips_STATUS_KILL_SHIFT )
    #define Upper_Lips_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Upper_Lips_STATUS_FIFOFULL_SHIFT)
    #define Upper_Lips_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Upper_Lips_STATUS_FIFONEMPTY_SHIFT)
    #define Upper_Lips_STATUS_TC              (uint8)((uint8)0x01u << Upper_Lips_STATUS_TC_SHIFT)
    #define Upper_Lips_STATUS_CMP2            (uint8)((uint8)0x01u << Upper_Lips_STATUS_CMP2_SHIFT)
    #define Upper_Lips_STATUS_CMP1            (uint8)((uint8)0x01u << Upper_Lips_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Upper_Lips_STATUS_KILL_INT_EN_MASK            (Upper_Lips_STATUS_KILL)
    #define Upper_Lips_STATUS_FIFOFULL_INT_EN_MASK        (Upper_Lips_STATUS_FIFOFULL)
    #define Upper_Lips_STATUS_FIFONEMPTY_INT_EN_MASK      (Upper_Lips_STATUS_FIFONEMPTY)
    #define Upper_Lips_STATUS_TC_INT_EN_MASK              (Upper_Lips_STATUS_TC)
    #define Upper_Lips_STATUS_CMP2_INT_EN_MASK            (Upper_Lips_STATUS_CMP2)
    #define Upper_Lips_STATUS_CMP1_INT_EN_MASK            (Upper_Lips_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Upper_Lips_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Upper_Lips_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Upper_Lips_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Upper_Lips_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Upper_Lips_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Upper_Lips_UsingFixedFunction */

#endif  /* CY_PWM_Upper_Lips_H */


/* [] END OF FILE */
