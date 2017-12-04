/*******************************************************************************
* File Name: Movers_Mover.h  
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

#if !defined(CY_PINS_Movers_Mover_H) /* Pins Movers_Mover_H */
#define CY_PINS_Movers_Mover_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Movers_Mover_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Movers_Mover__PORT == 15 && ((Movers_Mover__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Movers_Mover_Write(uint8 value);
void    Movers_Mover_SetDriveMode(uint8 mode);
uint8   Movers_Mover_ReadDataReg(void);
uint8   Movers_Mover_Read(void);
void    Movers_Mover_SetInterruptMode(uint16 position, uint16 mode);
uint8   Movers_Mover_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Movers_Mover_SetDriveMode() function.
     *  @{
     */
        #define Movers_Mover_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Movers_Mover_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Movers_Mover_DM_RES_UP          PIN_DM_RES_UP
        #define Movers_Mover_DM_RES_DWN         PIN_DM_RES_DWN
        #define Movers_Mover_DM_OD_LO           PIN_DM_OD_LO
        #define Movers_Mover_DM_OD_HI           PIN_DM_OD_HI
        #define Movers_Mover_DM_STRONG          PIN_DM_STRONG
        #define Movers_Mover_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Movers_Mover_MASK               Movers_Mover__MASK
#define Movers_Mover_SHIFT              Movers_Mover__SHIFT
#define Movers_Mover_WIDTH              1u

/* Interrupt constants */
#if defined(Movers_Mover__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Movers_Mover_SetInterruptMode() function.
     *  @{
     */
        #define Movers_Mover_INTR_NONE      (uint16)(0x0000u)
        #define Movers_Mover_INTR_RISING    (uint16)(0x0001u)
        #define Movers_Mover_INTR_FALLING   (uint16)(0x0002u)
        #define Movers_Mover_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Movers_Mover_INTR_MASK      (0x01u) 
#endif /* (Movers_Mover__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Movers_Mover_PS                     (* (reg8 *) Movers_Mover__PS)
/* Data Register */
#define Movers_Mover_DR                     (* (reg8 *) Movers_Mover__DR)
/* Port Number */
#define Movers_Mover_PRT_NUM                (* (reg8 *) Movers_Mover__PRT) 
/* Connect to Analog Globals */                                                  
#define Movers_Mover_AG                     (* (reg8 *) Movers_Mover__AG)                       
/* Analog MUX bux enable */
#define Movers_Mover_AMUX                   (* (reg8 *) Movers_Mover__AMUX) 
/* Bidirectional Enable */                                                        
#define Movers_Mover_BIE                    (* (reg8 *) Movers_Mover__BIE)
/* Bit-mask for Aliased Register Access */
#define Movers_Mover_BIT_MASK               (* (reg8 *) Movers_Mover__BIT_MASK)
/* Bypass Enable */
#define Movers_Mover_BYP                    (* (reg8 *) Movers_Mover__BYP)
/* Port wide control signals */                                                   
#define Movers_Mover_CTL                    (* (reg8 *) Movers_Mover__CTL)
/* Drive Modes */
#define Movers_Mover_DM0                    (* (reg8 *) Movers_Mover__DM0) 
#define Movers_Mover_DM1                    (* (reg8 *) Movers_Mover__DM1)
#define Movers_Mover_DM2                    (* (reg8 *) Movers_Mover__DM2) 
/* Input Buffer Disable Override */
#define Movers_Mover_INP_DIS                (* (reg8 *) Movers_Mover__INP_DIS)
/* LCD Common or Segment Drive */
#define Movers_Mover_LCD_COM_SEG            (* (reg8 *) Movers_Mover__LCD_COM_SEG)
/* Enable Segment LCD */
#define Movers_Mover_LCD_EN                 (* (reg8 *) Movers_Mover__LCD_EN)
/* Slew Rate Control */
#define Movers_Mover_SLW                    (* (reg8 *) Movers_Mover__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Movers_Mover_PRTDSI__CAPS_SEL       (* (reg8 *) Movers_Mover__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Movers_Mover_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Movers_Mover__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Movers_Mover_PRTDSI__OE_SEL0        (* (reg8 *) Movers_Mover__PRTDSI__OE_SEL0) 
#define Movers_Mover_PRTDSI__OE_SEL1        (* (reg8 *) Movers_Mover__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Movers_Mover_PRTDSI__OUT_SEL0       (* (reg8 *) Movers_Mover__PRTDSI__OUT_SEL0) 
#define Movers_Mover_PRTDSI__OUT_SEL1       (* (reg8 *) Movers_Mover__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Movers_Mover_PRTDSI__SYNC_OUT       (* (reg8 *) Movers_Mover__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Movers_Mover__SIO_CFG)
    #define Movers_Mover_SIO_HYST_EN        (* (reg8 *) Movers_Mover__SIO_HYST_EN)
    #define Movers_Mover_SIO_REG_HIFREQ     (* (reg8 *) Movers_Mover__SIO_REG_HIFREQ)
    #define Movers_Mover_SIO_CFG            (* (reg8 *) Movers_Mover__SIO_CFG)
    #define Movers_Mover_SIO_DIFF           (* (reg8 *) Movers_Mover__SIO_DIFF)
#endif /* (Movers_Mover__SIO_CFG) */

/* Interrupt Registers */
#if defined(Movers_Mover__INTSTAT)
    #define Movers_Mover_INTSTAT            (* (reg8 *) Movers_Mover__INTSTAT)
    #define Movers_Mover_SNAP               (* (reg8 *) Movers_Mover__SNAP)
    
	#define Movers_Mover_0_INTTYPE_REG 		(* (reg8 *) Movers_Mover__0__INTTYPE)
#endif /* (Movers_Mover__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Movers_Mover_H */


/* [] END OF FILE */
