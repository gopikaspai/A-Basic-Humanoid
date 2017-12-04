/*******************************************************************************
* File Name: Neuron_Mover.h  
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

#if !defined(CY_PINS_Neuron_Mover_H) /* Pins Neuron_Mover_H */
#define CY_PINS_Neuron_Mover_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Neuron_Mover_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Neuron_Mover__PORT == 15 && ((Neuron_Mover__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Neuron_Mover_Write(uint8 value);
void    Neuron_Mover_SetDriveMode(uint8 mode);
uint8   Neuron_Mover_ReadDataReg(void);
uint8   Neuron_Mover_Read(void);
void    Neuron_Mover_SetInterruptMode(uint16 position, uint16 mode);
uint8   Neuron_Mover_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Neuron_Mover_SetDriveMode() function.
     *  @{
     */
        #define Neuron_Mover_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Neuron_Mover_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Neuron_Mover_DM_RES_UP          PIN_DM_RES_UP
        #define Neuron_Mover_DM_RES_DWN         PIN_DM_RES_DWN
        #define Neuron_Mover_DM_OD_LO           PIN_DM_OD_LO
        #define Neuron_Mover_DM_OD_HI           PIN_DM_OD_HI
        #define Neuron_Mover_DM_STRONG          PIN_DM_STRONG
        #define Neuron_Mover_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Neuron_Mover_MASK               Neuron_Mover__MASK
#define Neuron_Mover_SHIFT              Neuron_Mover__SHIFT
#define Neuron_Mover_WIDTH              1u

/* Interrupt constants */
#if defined(Neuron_Mover__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Neuron_Mover_SetInterruptMode() function.
     *  @{
     */
        #define Neuron_Mover_INTR_NONE      (uint16)(0x0000u)
        #define Neuron_Mover_INTR_RISING    (uint16)(0x0001u)
        #define Neuron_Mover_INTR_FALLING   (uint16)(0x0002u)
        #define Neuron_Mover_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Neuron_Mover_INTR_MASK      (0x01u) 
#endif /* (Neuron_Mover__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Neuron_Mover_PS                     (* (reg8 *) Neuron_Mover__PS)
/* Data Register */
#define Neuron_Mover_DR                     (* (reg8 *) Neuron_Mover__DR)
/* Port Number */
#define Neuron_Mover_PRT_NUM                (* (reg8 *) Neuron_Mover__PRT) 
/* Connect to Analog Globals */                                                  
#define Neuron_Mover_AG                     (* (reg8 *) Neuron_Mover__AG)                       
/* Analog MUX bux enable */
#define Neuron_Mover_AMUX                   (* (reg8 *) Neuron_Mover__AMUX) 
/* Bidirectional Enable */                                                        
#define Neuron_Mover_BIE                    (* (reg8 *) Neuron_Mover__BIE)
/* Bit-mask for Aliased Register Access */
#define Neuron_Mover_BIT_MASK               (* (reg8 *) Neuron_Mover__BIT_MASK)
/* Bypass Enable */
#define Neuron_Mover_BYP                    (* (reg8 *) Neuron_Mover__BYP)
/* Port wide control signals */                                                   
#define Neuron_Mover_CTL                    (* (reg8 *) Neuron_Mover__CTL)
/* Drive Modes */
#define Neuron_Mover_DM0                    (* (reg8 *) Neuron_Mover__DM0) 
#define Neuron_Mover_DM1                    (* (reg8 *) Neuron_Mover__DM1)
#define Neuron_Mover_DM2                    (* (reg8 *) Neuron_Mover__DM2) 
/* Input Buffer Disable Override */
#define Neuron_Mover_INP_DIS                (* (reg8 *) Neuron_Mover__INP_DIS)
/* LCD Common or Segment Drive */
#define Neuron_Mover_LCD_COM_SEG            (* (reg8 *) Neuron_Mover__LCD_COM_SEG)
/* Enable Segment LCD */
#define Neuron_Mover_LCD_EN                 (* (reg8 *) Neuron_Mover__LCD_EN)
/* Slew Rate Control */
#define Neuron_Mover_SLW                    (* (reg8 *) Neuron_Mover__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Neuron_Mover_PRTDSI__CAPS_SEL       (* (reg8 *) Neuron_Mover__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Neuron_Mover_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Neuron_Mover__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Neuron_Mover_PRTDSI__OE_SEL0        (* (reg8 *) Neuron_Mover__PRTDSI__OE_SEL0) 
#define Neuron_Mover_PRTDSI__OE_SEL1        (* (reg8 *) Neuron_Mover__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Neuron_Mover_PRTDSI__OUT_SEL0       (* (reg8 *) Neuron_Mover__PRTDSI__OUT_SEL0) 
#define Neuron_Mover_PRTDSI__OUT_SEL1       (* (reg8 *) Neuron_Mover__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Neuron_Mover_PRTDSI__SYNC_OUT       (* (reg8 *) Neuron_Mover__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Neuron_Mover__SIO_CFG)
    #define Neuron_Mover_SIO_HYST_EN        (* (reg8 *) Neuron_Mover__SIO_HYST_EN)
    #define Neuron_Mover_SIO_REG_HIFREQ     (* (reg8 *) Neuron_Mover__SIO_REG_HIFREQ)
    #define Neuron_Mover_SIO_CFG            (* (reg8 *) Neuron_Mover__SIO_CFG)
    #define Neuron_Mover_SIO_DIFF           (* (reg8 *) Neuron_Mover__SIO_DIFF)
#endif /* (Neuron_Mover__SIO_CFG) */

/* Interrupt Registers */
#if defined(Neuron_Mover__INTSTAT)
    #define Neuron_Mover_INTSTAT            (* (reg8 *) Neuron_Mover__INTSTAT)
    #define Neuron_Mover_SNAP               (* (reg8 *) Neuron_Mover__SNAP)
    
	#define Neuron_Mover_0_INTTYPE_REG 		(* (reg8 *) Neuron_Mover__0__INTTYPE)
#endif /* (Neuron_Mover__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Neuron_Mover_H */


/* [] END OF FILE */
