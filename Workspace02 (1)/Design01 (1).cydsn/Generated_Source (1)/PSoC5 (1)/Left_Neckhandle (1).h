/*******************************************************************************
* File Name: Left_Neckhandle.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Left_Neckhandle_H) /* Pins Left_Neckhandle_H */
#define CY_PINS_Left_Neckhandle_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Left_Neckhandle_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Left_Neckhandle__PORT == 15 && ((Left_Neckhandle__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Left_Neckhandle_Write(uint8 value);
void    Left_Neckhandle_SetDriveMode(uint8 mode);
uint8   Left_Neckhandle_ReadDataReg(void);
uint8   Left_Neckhandle_Read(void);
void    Left_Neckhandle_SetInterruptMode(uint16 position, uint16 mode);
uint8   Left_Neckhandle_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Left_Neckhandle_SetDriveMode() function.
     *  @{
     */
        #define Left_Neckhandle_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Left_Neckhandle_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Left_Neckhandle_DM_RES_UP          PIN_DM_RES_UP
        #define Left_Neckhandle_DM_RES_DWN         PIN_DM_RES_DWN
        #define Left_Neckhandle_DM_OD_LO           PIN_DM_OD_LO
        #define Left_Neckhandle_DM_OD_HI           PIN_DM_OD_HI
        #define Left_Neckhandle_DM_STRONG          PIN_DM_STRONG
        #define Left_Neckhandle_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Left_Neckhandle_MASK               Left_Neckhandle__MASK
#define Left_Neckhandle_SHIFT              Left_Neckhandle__SHIFT
#define Left_Neckhandle_WIDTH              1u

/* Interrupt constants */
#if defined(Left_Neckhandle__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Left_Neckhandle_SetInterruptMode() function.
     *  @{
     */
        #define Left_Neckhandle_INTR_NONE      (uint16)(0x0000u)
        #define Left_Neckhandle_INTR_RISING    (uint16)(0x0001u)
        #define Left_Neckhandle_INTR_FALLING   (uint16)(0x0002u)
        #define Left_Neckhandle_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Left_Neckhandle_INTR_MASK      (0x01u) 
#endif /* (Left_Neckhandle__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Left_Neckhandle_PS                     (* (reg8 *) Left_Neckhandle__PS)
/* Data Register */
#define Left_Neckhandle_DR                     (* (reg8 *) Left_Neckhandle__DR)
/* Port Number */
#define Left_Neckhandle_PRT_NUM                (* (reg8 *) Left_Neckhandle__PRT) 
/* Connect to Analog Globals */                                                  
#define Left_Neckhandle_AG                     (* (reg8 *) Left_Neckhandle__AG)                       
/* Analog MUX bux enable */
#define Left_Neckhandle_AMUX                   (* (reg8 *) Left_Neckhandle__AMUX) 
/* Bidirectional Enable */                                                        
#define Left_Neckhandle_BIE                    (* (reg8 *) Left_Neckhandle__BIE)
/* Bit-mask for Aliased Register Access */
#define Left_Neckhandle_BIT_MASK               (* (reg8 *) Left_Neckhandle__BIT_MASK)
/* Bypass Enable */
#define Left_Neckhandle_BYP                    (* (reg8 *) Left_Neckhandle__BYP)
/* Port wide control signals */                                                   
#define Left_Neckhandle_CTL                    (* (reg8 *) Left_Neckhandle__CTL)
/* Drive Modes */
#define Left_Neckhandle_DM0                    (* (reg8 *) Left_Neckhandle__DM0) 
#define Left_Neckhandle_DM1                    (* (reg8 *) Left_Neckhandle__DM1)
#define Left_Neckhandle_DM2                    (* (reg8 *) Left_Neckhandle__DM2) 
/* Input Buffer Disable Override */
#define Left_Neckhandle_INP_DIS                (* (reg8 *) Left_Neckhandle__INP_DIS)
/* LCD Common or Segment Drive */
#define Left_Neckhandle_LCD_COM_SEG            (* (reg8 *) Left_Neckhandle__LCD_COM_SEG)
/* Enable Segment LCD */
#define Left_Neckhandle_LCD_EN                 (* (reg8 *) Left_Neckhandle__LCD_EN)
/* Slew Rate Control */
#define Left_Neckhandle_SLW                    (* (reg8 *) Left_Neckhandle__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Left_Neckhandle_PRTDSI__CAPS_SEL       (* (reg8 *) Left_Neckhandle__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Left_Neckhandle_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Left_Neckhandle__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Left_Neckhandle_PRTDSI__OE_SEL0        (* (reg8 *) Left_Neckhandle__PRTDSI__OE_SEL0) 
#define Left_Neckhandle_PRTDSI__OE_SEL1        (* (reg8 *) Left_Neckhandle__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Left_Neckhandle_PRTDSI__OUT_SEL0       (* (reg8 *) Left_Neckhandle__PRTDSI__OUT_SEL0) 
#define Left_Neckhandle_PRTDSI__OUT_SEL1       (* (reg8 *) Left_Neckhandle__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Left_Neckhandle_PRTDSI__SYNC_OUT       (* (reg8 *) Left_Neckhandle__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Left_Neckhandle__SIO_CFG)
    #define Left_Neckhandle_SIO_HYST_EN        (* (reg8 *) Left_Neckhandle__SIO_HYST_EN)
    #define Left_Neckhandle_SIO_REG_HIFREQ     (* (reg8 *) Left_Neckhandle__SIO_REG_HIFREQ)
    #define Left_Neckhandle_SIO_CFG            (* (reg8 *) Left_Neckhandle__SIO_CFG)
    #define Left_Neckhandle_SIO_DIFF           (* (reg8 *) Left_Neckhandle__SIO_DIFF)
#endif /* (Left_Neckhandle__SIO_CFG) */

/* Interrupt Registers */
#if defined(Left_Neckhandle__INTSTAT)
    #define Left_Neckhandle_INTSTAT            (* (reg8 *) Left_Neckhandle__INTSTAT)
    #define Left_Neckhandle_SNAP               (* (reg8 *) Left_Neckhandle__SNAP)
    
	#define Left_Neckhandle_0_INTTYPE_REG 		(* (reg8 *) Left_Neckhandle__0__INTTYPE)
#endif /* (Left_Neckhandle__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Left_Neckhandle_H */


/* [] END OF FILE */
