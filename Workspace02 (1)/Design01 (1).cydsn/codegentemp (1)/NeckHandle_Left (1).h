/*******************************************************************************
* File Name: NeckHandle_Left.h  
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

#if !defined(CY_PINS_NeckHandle_Left_H) /* Pins NeckHandle_Left_H */
#define CY_PINS_NeckHandle_Left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NeckHandle_Left_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NeckHandle_Left__PORT == 15 && ((NeckHandle_Left__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NeckHandle_Left_Write(uint8 value);
void    NeckHandle_Left_SetDriveMode(uint8 mode);
uint8   NeckHandle_Left_ReadDataReg(void);
uint8   NeckHandle_Left_Read(void);
void    NeckHandle_Left_SetInterruptMode(uint16 position, uint16 mode);
uint8   NeckHandle_Left_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NeckHandle_Left_SetDriveMode() function.
     *  @{
     */
        #define NeckHandle_Left_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NeckHandle_Left_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NeckHandle_Left_DM_RES_UP          PIN_DM_RES_UP
        #define NeckHandle_Left_DM_RES_DWN         PIN_DM_RES_DWN
        #define NeckHandle_Left_DM_OD_LO           PIN_DM_OD_LO
        #define NeckHandle_Left_DM_OD_HI           PIN_DM_OD_HI
        #define NeckHandle_Left_DM_STRONG          PIN_DM_STRONG
        #define NeckHandle_Left_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NeckHandle_Left_MASK               NeckHandle_Left__MASK
#define NeckHandle_Left_SHIFT              NeckHandle_Left__SHIFT
#define NeckHandle_Left_WIDTH              1u

/* Interrupt constants */
#if defined(NeckHandle_Left__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NeckHandle_Left_SetInterruptMode() function.
     *  @{
     */
        #define NeckHandle_Left_INTR_NONE      (uint16)(0x0000u)
        #define NeckHandle_Left_INTR_RISING    (uint16)(0x0001u)
        #define NeckHandle_Left_INTR_FALLING   (uint16)(0x0002u)
        #define NeckHandle_Left_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NeckHandle_Left_INTR_MASK      (0x01u) 
#endif /* (NeckHandle_Left__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NeckHandle_Left_PS                     (* (reg8 *) NeckHandle_Left__PS)
/* Data Register */
#define NeckHandle_Left_DR                     (* (reg8 *) NeckHandle_Left__DR)
/* Port Number */
#define NeckHandle_Left_PRT_NUM                (* (reg8 *) NeckHandle_Left__PRT) 
/* Connect to Analog Globals */                                                  
#define NeckHandle_Left_AG                     (* (reg8 *) NeckHandle_Left__AG)                       
/* Analog MUX bux enable */
#define NeckHandle_Left_AMUX                   (* (reg8 *) NeckHandle_Left__AMUX) 
/* Bidirectional Enable */                                                        
#define NeckHandle_Left_BIE                    (* (reg8 *) NeckHandle_Left__BIE)
/* Bit-mask for Aliased Register Access */
#define NeckHandle_Left_BIT_MASK               (* (reg8 *) NeckHandle_Left__BIT_MASK)
/* Bypass Enable */
#define NeckHandle_Left_BYP                    (* (reg8 *) NeckHandle_Left__BYP)
/* Port wide control signals */                                                   
#define NeckHandle_Left_CTL                    (* (reg8 *) NeckHandle_Left__CTL)
/* Drive Modes */
#define NeckHandle_Left_DM0                    (* (reg8 *) NeckHandle_Left__DM0) 
#define NeckHandle_Left_DM1                    (* (reg8 *) NeckHandle_Left__DM1)
#define NeckHandle_Left_DM2                    (* (reg8 *) NeckHandle_Left__DM2) 
/* Input Buffer Disable Override */
#define NeckHandle_Left_INP_DIS                (* (reg8 *) NeckHandle_Left__INP_DIS)
/* LCD Common or Segment Drive */
#define NeckHandle_Left_LCD_COM_SEG            (* (reg8 *) NeckHandle_Left__LCD_COM_SEG)
/* Enable Segment LCD */
#define NeckHandle_Left_LCD_EN                 (* (reg8 *) NeckHandle_Left__LCD_EN)
/* Slew Rate Control */
#define NeckHandle_Left_SLW                    (* (reg8 *) NeckHandle_Left__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NeckHandle_Left_PRTDSI__CAPS_SEL       (* (reg8 *) NeckHandle_Left__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NeckHandle_Left_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NeckHandle_Left__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NeckHandle_Left_PRTDSI__OE_SEL0        (* (reg8 *) NeckHandle_Left__PRTDSI__OE_SEL0) 
#define NeckHandle_Left_PRTDSI__OE_SEL1        (* (reg8 *) NeckHandle_Left__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NeckHandle_Left_PRTDSI__OUT_SEL0       (* (reg8 *) NeckHandle_Left__PRTDSI__OUT_SEL0) 
#define NeckHandle_Left_PRTDSI__OUT_SEL1       (* (reg8 *) NeckHandle_Left__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NeckHandle_Left_PRTDSI__SYNC_OUT       (* (reg8 *) NeckHandle_Left__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NeckHandle_Left__SIO_CFG)
    #define NeckHandle_Left_SIO_HYST_EN        (* (reg8 *) NeckHandle_Left__SIO_HYST_EN)
    #define NeckHandle_Left_SIO_REG_HIFREQ     (* (reg8 *) NeckHandle_Left__SIO_REG_HIFREQ)
    #define NeckHandle_Left_SIO_CFG            (* (reg8 *) NeckHandle_Left__SIO_CFG)
    #define NeckHandle_Left_SIO_DIFF           (* (reg8 *) NeckHandle_Left__SIO_DIFF)
#endif /* (NeckHandle_Left__SIO_CFG) */

/* Interrupt Registers */
#if defined(NeckHandle_Left__INTSTAT)
    #define NeckHandle_Left_INTSTAT            (* (reg8 *) NeckHandle_Left__INTSTAT)
    #define NeckHandle_Left_SNAP               (* (reg8 *) NeckHandle_Left__SNAP)
    
	#define NeckHandle_Left_0_INTTYPE_REG 		(* (reg8 *) NeckHandle_Left__0__INTTYPE)
#endif /* (NeckHandle_Left__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NeckHandle_Left_H */


/* [] END OF FILE */
