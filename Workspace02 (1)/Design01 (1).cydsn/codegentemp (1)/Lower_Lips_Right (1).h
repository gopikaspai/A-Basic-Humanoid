/*******************************************************************************
* File Name: Lower_Lips_Right.h  
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

#if !defined(CY_PINS_Lower_Lips_Right_H) /* Pins Lower_Lips_Right_H */
#define CY_PINS_Lower_Lips_Right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Lower_Lips_Right_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Lower_Lips_Right__PORT == 15 && ((Lower_Lips_Right__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Lower_Lips_Right_Write(uint8 value);
void    Lower_Lips_Right_SetDriveMode(uint8 mode);
uint8   Lower_Lips_Right_ReadDataReg(void);
uint8   Lower_Lips_Right_Read(void);
void    Lower_Lips_Right_SetInterruptMode(uint16 position, uint16 mode);
uint8   Lower_Lips_Right_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Lower_Lips_Right_SetDriveMode() function.
     *  @{
     */
        #define Lower_Lips_Right_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Lower_Lips_Right_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Lower_Lips_Right_DM_RES_UP          PIN_DM_RES_UP
        #define Lower_Lips_Right_DM_RES_DWN         PIN_DM_RES_DWN
        #define Lower_Lips_Right_DM_OD_LO           PIN_DM_OD_LO
        #define Lower_Lips_Right_DM_OD_HI           PIN_DM_OD_HI
        #define Lower_Lips_Right_DM_STRONG          PIN_DM_STRONG
        #define Lower_Lips_Right_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Lower_Lips_Right_MASK               Lower_Lips_Right__MASK
#define Lower_Lips_Right_SHIFT              Lower_Lips_Right__SHIFT
#define Lower_Lips_Right_WIDTH              1u

/* Interrupt constants */
#if defined(Lower_Lips_Right__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Lower_Lips_Right_SetInterruptMode() function.
     *  @{
     */
        #define Lower_Lips_Right_INTR_NONE      (uint16)(0x0000u)
        #define Lower_Lips_Right_INTR_RISING    (uint16)(0x0001u)
        #define Lower_Lips_Right_INTR_FALLING   (uint16)(0x0002u)
        #define Lower_Lips_Right_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Lower_Lips_Right_INTR_MASK      (0x01u) 
#endif /* (Lower_Lips_Right__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Lower_Lips_Right_PS                     (* (reg8 *) Lower_Lips_Right__PS)
/* Data Register */
#define Lower_Lips_Right_DR                     (* (reg8 *) Lower_Lips_Right__DR)
/* Port Number */
#define Lower_Lips_Right_PRT_NUM                (* (reg8 *) Lower_Lips_Right__PRT) 
/* Connect to Analog Globals */                                                  
#define Lower_Lips_Right_AG                     (* (reg8 *) Lower_Lips_Right__AG)                       
/* Analog MUX bux enable */
#define Lower_Lips_Right_AMUX                   (* (reg8 *) Lower_Lips_Right__AMUX) 
/* Bidirectional Enable */                                                        
#define Lower_Lips_Right_BIE                    (* (reg8 *) Lower_Lips_Right__BIE)
/* Bit-mask for Aliased Register Access */
#define Lower_Lips_Right_BIT_MASK               (* (reg8 *) Lower_Lips_Right__BIT_MASK)
/* Bypass Enable */
#define Lower_Lips_Right_BYP                    (* (reg8 *) Lower_Lips_Right__BYP)
/* Port wide control signals */                                                   
#define Lower_Lips_Right_CTL                    (* (reg8 *) Lower_Lips_Right__CTL)
/* Drive Modes */
#define Lower_Lips_Right_DM0                    (* (reg8 *) Lower_Lips_Right__DM0) 
#define Lower_Lips_Right_DM1                    (* (reg8 *) Lower_Lips_Right__DM1)
#define Lower_Lips_Right_DM2                    (* (reg8 *) Lower_Lips_Right__DM2) 
/* Input Buffer Disable Override */
#define Lower_Lips_Right_INP_DIS                (* (reg8 *) Lower_Lips_Right__INP_DIS)
/* LCD Common or Segment Drive */
#define Lower_Lips_Right_LCD_COM_SEG            (* (reg8 *) Lower_Lips_Right__LCD_COM_SEG)
/* Enable Segment LCD */
#define Lower_Lips_Right_LCD_EN                 (* (reg8 *) Lower_Lips_Right__LCD_EN)
/* Slew Rate Control */
#define Lower_Lips_Right_SLW                    (* (reg8 *) Lower_Lips_Right__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Lower_Lips_Right_PRTDSI__CAPS_SEL       (* (reg8 *) Lower_Lips_Right__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Lower_Lips_Right_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Lower_Lips_Right__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Lower_Lips_Right_PRTDSI__OE_SEL0        (* (reg8 *) Lower_Lips_Right__PRTDSI__OE_SEL0) 
#define Lower_Lips_Right_PRTDSI__OE_SEL1        (* (reg8 *) Lower_Lips_Right__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Lower_Lips_Right_PRTDSI__OUT_SEL0       (* (reg8 *) Lower_Lips_Right__PRTDSI__OUT_SEL0) 
#define Lower_Lips_Right_PRTDSI__OUT_SEL1       (* (reg8 *) Lower_Lips_Right__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Lower_Lips_Right_PRTDSI__SYNC_OUT       (* (reg8 *) Lower_Lips_Right__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Lower_Lips_Right__SIO_CFG)
    #define Lower_Lips_Right_SIO_HYST_EN        (* (reg8 *) Lower_Lips_Right__SIO_HYST_EN)
    #define Lower_Lips_Right_SIO_REG_HIFREQ     (* (reg8 *) Lower_Lips_Right__SIO_REG_HIFREQ)
    #define Lower_Lips_Right_SIO_CFG            (* (reg8 *) Lower_Lips_Right__SIO_CFG)
    #define Lower_Lips_Right_SIO_DIFF           (* (reg8 *) Lower_Lips_Right__SIO_DIFF)
#endif /* (Lower_Lips_Right__SIO_CFG) */

/* Interrupt Registers */
#if defined(Lower_Lips_Right__INTSTAT)
    #define Lower_Lips_Right_INTSTAT            (* (reg8 *) Lower_Lips_Right__INTSTAT)
    #define Lower_Lips_Right_SNAP               (* (reg8 *) Lower_Lips_Right__SNAP)
    
	#define Lower_Lips_Right_0_INTTYPE_REG 		(* (reg8 *) Lower_Lips_Right__0__INTTYPE)
#endif /* (Lower_Lips_Right__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Lower_Lips_Right_H */


/* [] END OF FILE */
