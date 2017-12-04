/*******************************************************************************
* File Name: Eye_Rod.h
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

#if !defined(CY_PWM_Eye_Rod_H)
#define CY_PWM_Eye_Rod_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Eye_Rod_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Eye_Rod_Resolution                     (16u)
#define Eye_Rod_UsingFixedFunction             (0u)
#define Eye_Rod_DeadBandMode                   (0u)
#define Eye_Rod_KillModeMinTime                (0u)
#define Eye_Rod_KillMode                       (0u)
#define Eye_Rod_PWMMode                        (1u)
#define Eye_Rod_PWMModeIsCenterAligned         (0u)
#define Eye_Rod_DeadBandUsed                   (0u)
#define Eye_Rod_DeadBand2_4                    (0u)

#if !defined(Eye_Rod_PWMUDB_genblk8_stsreg__REMOVED)
    #define Eye_Rod_UseStatus                  (1u)
#else
    #define Eye_Rod_UseStatus                  (0u)
#endif /* !defined(Eye_Rod_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Eye_Rod_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Eye_Rod_UseControl                 (1u)
#else
    #define Eye_Rod_UseControl                 (0u)
#endif /* !defined(Eye_Rod_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Eye_Rod_UseOneCompareMode              (0u)
#define Eye_Rod_MinimumKillTime                (1u)
#define Eye_Rod_EnableMode                     (0u)

#define Eye_Rod_CompareMode1SW                 (0u)
#define Eye_Rod_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Eye_Rod__B_PWM__DISABLED 0
#define Eye_Rod__B_PWM__ASYNCHRONOUS 1
#define Eye_Rod__B_PWM__SINGLECYCLE 2
#define Eye_Rod__B_PWM__LATCHED 3
#define Eye_Rod__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Eye_Rod__B_PWM__DBMDISABLED 0
#define Eye_Rod__B_PWM__DBM_2_4_CLOCKS 1
#define Eye_Rod__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Eye_Rod__B_PWM__ONE_OUTPUT 0
#define Eye_Rod__B_PWM__TWO_OUTPUTS 1
#define Eye_Rod__B_PWM__DUAL_EDGE 2
#define Eye_Rod__B_PWM__CENTER_ALIGN 3
#define Eye_Rod__B_PWM__DITHER 5
#define Eye_Rod__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Eye_Rod__B_PWM__LESS_THAN 1
#define Eye_Rod__B_PWM__LESS_THAN_OR_EQUAL 2
#define Eye_Rod__B_PWM__GREATER_THAN 3
#define Eye_Rod__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Eye_Rod__B_PWM__EQUAL 0
#define Eye_Rod__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Eye_Rod_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Eye_Rod_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Eye_Rod_PWMModeIsCenterAligned) */
        #if (Eye_Rod_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Eye_Rod_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_256_CLOCKS || \
            Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Eye_Rod_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Eye_Rod_KillModeMinTime) */

        /* Backup control register */
        #if(Eye_Rod_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Eye_Rod_UseControl) */

    #endif /* (!Eye_Rod_UsingFixedFunction) */

}Eye_Rod_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Eye_Rod_Start(void) ;
void    Eye_Rod_Stop(void) ;

#if (Eye_Rod_UseStatus || Eye_Rod_UsingFixedFunction)
    void  Eye_Rod_SetInterruptMode(uint8 interruptMode) ;
    uint8 Eye_Rod_ReadStatusRegister(void) ;
#endif /* (Eye_Rod_UseStatus || Eye_Rod_UsingFixedFunction) */

#define Eye_Rod_GetInterruptSource() Eye_Rod_ReadStatusRegister()

#if (Eye_Rod_UseControl)
    uint8 Eye_Rod_ReadControlRegister(void) ;
    void  Eye_Rod_WriteControlRegister(uint8 control)
          ;
#endif /* (Eye_Rod_UseControl) */

#if (Eye_Rod_UseOneCompareMode)
   #if (Eye_Rod_CompareMode1SW)
       void    Eye_Rod_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Eye_Rod_CompareMode1SW) */
#else
    #if (Eye_Rod_CompareMode1SW)
        void    Eye_Rod_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Eye_Rod_CompareMode1SW) */
    #if (Eye_Rod_CompareMode2SW)
        void    Eye_Rod_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Eye_Rod_CompareMode2SW) */
#endif /* (Eye_Rod_UseOneCompareMode) */

#if (!Eye_Rod_UsingFixedFunction)
    uint16   Eye_Rod_ReadCounter(void) ;
    uint16 Eye_Rod_ReadCapture(void) ;

    #if (Eye_Rod_UseStatus)
            void Eye_Rod_ClearFIFO(void) ;
    #endif /* (Eye_Rod_UseStatus) */

    void    Eye_Rod_WriteCounter(uint16 counter)
            ;
#endif /* (!Eye_Rod_UsingFixedFunction) */

void    Eye_Rod_WritePeriod(uint16 period)
        ;
uint16 Eye_Rod_ReadPeriod(void) ;

#if (Eye_Rod_UseOneCompareMode)
    void    Eye_Rod_WriteCompare(uint16 compare)
            ;
    uint16 Eye_Rod_ReadCompare(void) ;
#else
    void    Eye_Rod_WriteCompare1(uint16 compare)
            ;
    uint16 Eye_Rod_ReadCompare1(void) ;
    void    Eye_Rod_WriteCompare2(uint16 compare)
            ;
    uint16 Eye_Rod_ReadCompare2(void) ;
#endif /* (Eye_Rod_UseOneCompareMode) */


#if (Eye_Rod_DeadBandUsed)
    void    Eye_Rod_WriteDeadTime(uint8 deadtime) ;
    uint8   Eye_Rod_ReadDeadTime(void) ;
#endif /* (Eye_Rod_DeadBandUsed) */

#if ( Eye_Rod_KillModeMinTime)
    void Eye_Rod_WriteKillTime(uint8 killtime) ;
    uint8 Eye_Rod_ReadKillTime(void) ;
#endif /* ( Eye_Rod_KillModeMinTime) */

void Eye_Rod_Init(void) ;
void Eye_Rod_Enable(void) ;
void Eye_Rod_Sleep(void) ;
void Eye_Rod_Wakeup(void) ;
void Eye_Rod_SaveConfig(void) ;
void Eye_Rod_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Eye_Rod_INIT_PERIOD_VALUE          (60000u)
#define Eye_Rod_INIT_COMPARE_VALUE1        (0u)
#define Eye_Rod_INIT_COMPARE_VALUE2        (0u)
#define Eye_Rod_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Eye_Rod_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eye_Rod_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eye_Rod_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Eye_Rod_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Eye_Rod_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Eye_Rod_CTRL_CMPMODE2_SHIFT)
#define Eye_Rod_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Eye_Rod_CTRL_CMPMODE1_SHIFT)
#define Eye_Rod_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Eye_Rod_UsingFixedFunction)
   #define Eye_Rod_PERIOD_LSB              (*(reg16 *) Eye_Rod_PWMHW__PER0)
   #define Eye_Rod_PERIOD_LSB_PTR          ( (reg16 *) Eye_Rod_PWMHW__PER0)
   #define Eye_Rod_COMPARE1_LSB            (*(reg16 *) Eye_Rod_PWMHW__CNT_CMP0)
   #define Eye_Rod_COMPARE1_LSB_PTR        ( (reg16 *) Eye_Rod_PWMHW__CNT_CMP0)
   #define Eye_Rod_COMPARE2_LSB            (0x00u)
   #define Eye_Rod_COMPARE2_LSB_PTR        (0x00u)
   #define Eye_Rod_COUNTER_LSB             (*(reg16 *) Eye_Rod_PWMHW__CNT_CMP0)
   #define Eye_Rod_COUNTER_LSB_PTR         ( (reg16 *) Eye_Rod_PWMHW__CNT_CMP0)
   #define Eye_Rod_CAPTURE_LSB             (*(reg16 *) Eye_Rod_PWMHW__CAP0)
   #define Eye_Rod_CAPTURE_LSB_PTR         ( (reg16 *) Eye_Rod_PWMHW__CAP0)
   #define Eye_Rod_RT1                     (*(reg8 *)  Eye_Rod_PWMHW__RT1)
   #define Eye_Rod_RT1_PTR                 ( (reg8 *)  Eye_Rod_PWMHW__RT1)

#else
   #if (Eye_Rod_Resolution == 8u) /* 8bit - PWM */

       #if(Eye_Rod_PWMModeIsCenterAligned)
           #define Eye_Rod_PERIOD_LSB      (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Eye_Rod_PERIOD_LSB_PTR  ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Eye_Rod_PERIOD_LSB      (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Eye_Rod_PERIOD_LSB_PTR  ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Eye_Rod_PWMModeIsCenterAligned) */

       #define Eye_Rod_COMPARE1_LSB        (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Eye_Rod_COMPARE1_LSB_PTR    ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Eye_Rod_COMPARE2_LSB        (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Eye_Rod_COMPARE2_LSB_PTR    ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Eye_Rod_COUNTERCAP_LSB      (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Eye_Rod_COUNTERCAP_LSB_PTR  ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Eye_Rod_COUNTER_LSB         (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Eye_Rod_COUNTER_LSB_PTR     ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Eye_Rod_CAPTURE_LSB         (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Eye_Rod_CAPTURE_LSB_PTR     ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Eye_Rod_PWMModeIsCenterAligned)
               #define Eye_Rod_PERIOD_LSB      (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Eye_Rod_PERIOD_LSB_PTR  ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Eye_Rod_PERIOD_LSB      (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Eye_Rod_PERIOD_LSB_PTR  ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Eye_Rod_PWMModeIsCenterAligned) */

            #define Eye_Rod_COMPARE1_LSB       (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Eye_Rod_COMPARE1_LSB_PTR   ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Eye_Rod_COMPARE2_LSB       (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Eye_Rod_COMPARE2_LSB_PTR   ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Eye_Rod_COUNTERCAP_LSB     (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Eye_Rod_COUNTERCAP_LSB_PTR ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Eye_Rod_COUNTER_LSB        (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Eye_Rod_COUNTER_LSB_PTR    ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Eye_Rod_CAPTURE_LSB        (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Eye_Rod_CAPTURE_LSB_PTR    ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Eye_Rod_PWMModeIsCenterAligned)
               #define Eye_Rod_PERIOD_LSB      (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Eye_Rod_PERIOD_LSB_PTR  ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Eye_Rod_PERIOD_LSB      (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Eye_Rod_PERIOD_LSB_PTR  ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Eye_Rod_PWMModeIsCenterAligned) */

            #define Eye_Rod_COMPARE1_LSB       (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Eye_Rod_COMPARE1_LSB_PTR   ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Eye_Rod_COMPARE2_LSB       (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Eye_Rod_COMPARE2_LSB_PTR   ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Eye_Rod_COUNTERCAP_LSB     (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Eye_Rod_COUNTERCAP_LSB_PTR ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Eye_Rod_COUNTER_LSB        (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Eye_Rod_COUNTER_LSB_PTR    ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Eye_Rod_CAPTURE_LSB        (*(reg16 *) Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Eye_Rod_CAPTURE_LSB_PTR    ((reg16 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Eye_Rod_AUX_CONTROLDP1          (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Eye_Rod_AUX_CONTROLDP1_PTR      ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Eye_Rod_Resolution == 8) */

   #define Eye_Rod_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Eye_Rod_AUX_CONTROLDP0          (*(reg8 *)  Eye_Rod_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Eye_Rod_AUX_CONTROLDP0_PTR      ((reg8 *)   Eye_Rod_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Eye_Rod_UsingFixedFunction) */

#if(Eye_Rod_KillModeMinTime )
    #define Eye_Rod_KILLMODEMINTIME        (*(reg8 *)  Eye_Rod_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Eye_Rod_KILLMODEMINTIME_PTR    ((reg8 *)   Eye_Rod_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Eye_Rod_KillModeMinTime ) */

#if(Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_256_CLOCKS)
    #define Eye_Rod_DEADBAND_COUNT         (*(reg8 *)  Eye_Rod_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Eye_Rod_DEADBAND_COUNT_PTR     ((reg8 *)   Eye_Rod_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Eye_Rod_DEADBAND_LSB_PTR       ((reg8 *)   Eye_Rod_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Eye_Rod_DEADBAND_LSB           (*(reg8 *)  Eye_Rod_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Eye_Rod_UsingFixedFunction)
        #define Eye_Rod_DEADBAND_COUNT         (*(reg8 *)  Eye_Rod_PWMHW__CFG0)
        #define Eye_Rod_DEADBAND_COUNT_PTR     ((reg8 *)   Eye_Rod_PWMHW__CFG0)
        #define Eye_Rod_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Eye_Rod_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Eye_Rod_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Eye_Rod_DEADBAND_COUNT         (*(reg8 *)  Eye_Rod_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Eye_Rod_DEADBAND_COUNT_PTR     ((reg8 *)   Eye_Rod_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Eye_Rod_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Eye_Rod_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Eye_Rod_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Eye_Rod_UsingFixedFunction) */
#endif /* (Eye_Rod_DeadBandMode == Eye_Rod__B_PWM__DBM_256_CLOCKS) */



#if (Eye_Rod_UsingFixedFunction)
    #define Eye_Rod_STATUS                 (*(reg8 *) Eye_Rod_PWMHW__SR0)
    #define Eye_Rod_STATUS_PTR             ((reg8 *) Eye_Rod_PWMHW__SR0)
    #define Eye_Rod_STATUS_MASK            (*(reg8 *) Eye_Rod_PWMHW__SR0)
    #define Eye_Rod_STATUS_MASK_PTR        ((reg8 *) Eye_Rod_PWMHW__SR0)
    #define Eye_Rod_CONTROL                (*(reg8 *) Eye_Rod_PWMHW__CFG0)
    #define Eye_Rod_CONTROL_PTR            ((reg8 *) Eye_Rod_PWMHW__CFG0)
    #define Eye_Rod_CONTROL2               (*(reg8 *) Eye_Rod_PWMHW__CFG1)
    #define Eye_Rod_CONTROL3               (*(reg8 *) Eye_Rod_PWMHW__CFG2)
    #define Eye_Rod_GLOBAL_ENABLE          (*(reg8 *) Eye_Rod_PWMHW__PM_ACT_CFG)
    #define Eye_Rod_GLOBAL_ENABLE_PTR      ( (reg8 *) Eye_Rod_PWMHW__PM_ACT_CFG)
    #define Eye_Rod_GLOBAL_STBY_ENABLE     (*(reg8 *) Eye_Rod_PWMHW__PM_STBY_CFG)
    #define Eye_Rod_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Eye_Rod_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Eye_Rod_BLOCK_EN_MASK          (Eye_Rod_PWMHW__PM_ACT_MSK)
    #define Eye_Rod_BLOCK_STBY_EN_MASK     (Eye_Rod_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Eye_Rod_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Eye_Rod_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Eye_Rod_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Eye_Rod_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Eye_Rod_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Eye_Rod_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Eye_Rod_CTRL_ENABLE            (uint8)((uint8)0x01u << Eye_Rod_CTRL_ENABLE_SHIFT)
    #define Eye_Rod_CTRL_RESET             (uint8)((uint8)0x01u << Eye_Rod_CTRL_RESET_SHIFT)
    #define Eye_Rod_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Eye_Rod_CTRL_CMPMODE2_SHIFT)
    #define Eye_Rod_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Eye_Rod_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Eye_Rod_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Eye_Rod_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Eye_Rod_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Eye_Rod_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Eye_Rod_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Eye_Rod_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Eye_Rod_STATUS_TC_INT_EN_MASK_SHIFT            (Eye_Rod_STATUS_TC_SHIFT - 4u)
    #define Eye_Rod_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Eye_Rod_STATUS_CMP1_INT_EN_MASK_SHIFT          (Eye_Rod_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Eye_Rod_STATUS_TC              (uint8)((uint8)0x01u << Eye_Rod_STATUS_TC_SHIFT)
    #define Eye_Rod_STATUS_CMP1            (uint8)((uint8)0x01u << Eye_Rod_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Eye_Rod_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Eye_Rod_STATUS_TC >> 4u)
    #define Eye_Rod_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Eye_Rod_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Eye_Rod_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Eye_Rod_RT1_MASK              (uint8)((uint8)0x03u << Eye_Rod_RT1_SHIFT)
    #define Eye_Rod_SYNC                  (uint8)((uint8)0x03u << Eye_Rod_RT1_SHIFT)
    #define Eye_Rod_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Eye_Rod_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Eye_Rod_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Eye_Rod_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Eye_Rod_SYNCDSI_SHIFT)


#else
    #define Eye_Rod_STATUS                (*(reg8 *)   Eye_Rod_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Eye_Rod_STATUS_PTR            ((reg8 *)    Eye_Rod_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Eye_Rod_STATUS_MASK           (*(reg8 *)   Eye_Rod_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Eye_Rod_STATUS_MASK_PTR       ((reg8 *)    Eye_Rod_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Eye_Rod_STATUS_AUX_CTRL       (*(reg8 *)   Eye_Rod_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Eye_Rod_CONTROL               (*(reg8 *)   Eye_Rod_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Eye_Rod_CONTROL_PTR           ((reg8 *)    Eye_Rod_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Eye_Rod_CTRL_ENABLE_SHIFT      (0x07u)
    #define Eye_Rod_CTRL_RESET_SHIFT       (0x06u)
    #define Eye_Rod_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Eye_Rod_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Eye_Rod_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Eye_Rod_CTRL_ENABLE            (uint8)((uint8)0x01u << Eye_Rod_CTRL_ENABLE_SHIFT)
    #define Eye_Rod_CTRL_RESET             (uint8)((uint8)0x01u << Eye_Rod_CTRL_RESET_SHIFT)
    #define Eye_Rod_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Eye_Rod_CTRL_CMPMODE2_SHIFT)
    #define Eye_Rod_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Eye_Rod_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Eye_Rod_STATUS_KILL_SHIFT          (0x05u)
    #define Eye_Rod_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Eye_Rod_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Eye_Rod_STATUS_TC_SHIFT            (0x02u)
    #define Eye_Rod_STATUS_CMP2_SHIFT          (0x01u)
    #define Eye_Rod_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Eye_Rod_STATUS_KILL_INT_EN_MASK_SHIFT          (Eye_Rod_STATUS_KILL_SHIFT)
    #define Eye_Rod_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Eye_Rod_STATUS_FIFONEMPTY_SHIFT)
    #define Eye_Rod_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Eye_Rod_STATUS_FIFOFULL_SHIFT)
    #define Eye_Rod_STATUS_TC_INT_EN_MASK_SHIFT            (Eye_Rod_STATUS_TC_SHIFT)
    #define Eye_Rod_STATUS_CMP2_INT_EN_MASK_SHIFT          (Eye_Rod_STATUS_CMP2_SHIFT)
    #define Eye_Rod_STATUS_CMP1_INT_EN_MASK_SHIFT          (Eye_Rod_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Eye_Rod_STATUS_KILL            (uint8)((uint8)0x00u << Eye_Rod_STATUS_KILL_SHIFT )
    #define Eye_Rod_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Eye_Rod_STATUS_FIFOFULL_SHIFT)
    #define Eye_Rod_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Eye_Rod_STATUS_FIFONEMPTY_SHIFT)
    #define Eye_Rod_STATUS_TC              (uint8)((uint8)0x01u << Eye_Rod_STATUS_TC_SHIFT)
    #define Eye_Rod_STATUS_CMP2            (uint8)((uint8)0x01u << Eye_Rod_STATUS_CMP2_SHIFT)
    #define Eye_Rod_STATUS_CMP1            (uint8)((uint8)0x01u << Eye_Rod_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Eye_Rod_STATUS_KILL_INT_EN_MASK            (Eye_Rod_STATUS_KILL)
    #define Eye_Rod_STATUS_FIFOFULL_INT_EN_MASK        (Eye_Rod_STATUS_FIFOFULL)
    #define Eye_Rod_STATUS_FIFONEMPTY_INT_EN_MASK      (Eye_Rod_STATUS_FIFONEMPTY)
    #define Eye_Rod_STATUS_TC_INT_EN_MASK              (Eye_Rod_STATUS_TC)
    #define Eye_Rod_STATUS_CMP2_INT_EN_MASK            (Eye_Rod_STATUS_CMP2)
    #define Eye_Rod_STATUS_CMP1_INT_EN_MASK            (Eye_Rod_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Eye_Rod_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Eye_Rod_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Eye_Rod_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Eye_Rod_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Eye_Rod_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Eye_Rod_UsingFixedFunction */

#endif  /* CY_PWM_Eye_Rod_H */


/* [] END OF FILE */
