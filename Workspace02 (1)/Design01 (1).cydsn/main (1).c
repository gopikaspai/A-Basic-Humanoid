/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

void beatbox()
{
    int i = 0;
    Upper_Lips_Start();
    Lower_Lips_Start();
    for(i = 0; i < 5; i++)
    {
        Upper_Lips_WriteCompare1(1500);
        Upper_Lips_WriteCompare2(1500);
        CyDelay(500);
        Upper_Lips_WriteCompare1(3500);
        Upper_Lips_WriteCompare2(3500);
        CyDelay(500);
        Lower_Lips_WriteCompare1(1500);
        Lower_Lips_WriteCompare2(1500);
        CyDelay(100);
        Lower_Lips_WriteCompare1(3500);
        Lower_Lips_WriteCompare2(3500);
        CyDelay(100);
    }
 }

int main(void)
{
   /* int i = 0;
    Right_Eyebrow_Start();
    Left_Eyebrow_Start();
    for(i = 0;i < 8;i++)
    {
        Right_Eyebrow_WriteCompare1(2000);
        Right_Eyebrow_WriteCompare2(12000);
        CyDelay(500);
        Right_Eyebrow_WriteCompare1(3500);
        Right_Eyebrow_WriteCompare2(6000);
        CyDelay(100);
        Left_Eyebrow_WriteCompare1(10000);
        Left_Eyebrow_WriteCompare2(4000);
        CyDelay(500);
        Left_Eyebrow_WriteCompare1(6500);
        Left_Eyebrow_WriteCompare2(7000);
        CyDelay(100); 
    } */
        
   /* Right_Eyeball_Start();
    int j;
    for(j=0;j<50;i++)
    {
    Right_Eyeball_WriteCompare1(1500);
    Right_Eyeball_WriteCompare2(1500);
    CyDelay(1000);
    Right_Eyeball_WriteCompare1(3500);
    Right_Eyeball_WriteCompare2(3500);
    CyDelay(1000);
    }
    
    Left_Eyeball_Start();
    for(i = 0;i < 10;i++)
    {
    Left_Eyeball_WriteCompare1(1500);
    Left_Eyeball_WriteCompare2(1500);
    CyDelay(1000);
    Left_Eyeball_WriteCompare1(3500);
    Left_Eyeball_WriteCompare2(3500);
    CyDelay(1000);
    }
    */
    /*int i = 0;
    Upper_Lips_Start();
    Lower_Lips_Start();
    for(i = 0; i < 5; i++)
    {
        Upper_Lips_WriteCompare1(2000);
        Upper_Lips_WriteCompare2(3000);
        CyDelay(100);
        Lower_Lips_WriteCompare2(12000);
        CyDelay(500);
        Upper_Lips_WriteCompare1(3000);
        Upper_Lips_WriteCompare2(2000);
        CyDelay(100); 
        Lower_Lips_WriteCompare2(6000);
        CyDelay(500);
       
    }*/
    
    int i;
    NeckHandle_Start();
    for(i = 0;i < 2;i++)
    {
    NeckHandle_WriteCompare1(1000);
    //NeckHandle_WriteCompare2(1500);
    CyDelay(100);
    NeckHandle_WriteCompare1(2000);
    CyDelay(100);
    NeckHandle_WriteCompare1(1000);
    //NeckHandle_WriteCompare2(3500);
    CyDelay(100);
    }
        
    /*
    Eye_Rod_Start();
    for(i = 0;i < 10;i++)
    {
    Eye_Rod_WriteCompare1(1500);
    Eye_Rod_WriteCompare2(1500);
    CyDelay(1000);
    Eye_Rod_WriteCompare1(3500);
    Eye_Rod_WriteCompare2(3500);
    CyDelay(1000);
    }*/
    
  
}
/* [] END OF FILE */
