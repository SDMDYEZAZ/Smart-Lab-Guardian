/************************************************************/
/* File Name : ir.c                                         */
/* Description : Contains function definitions of ir sensor */
/* Controller : LPC2129 / LPC2148                           */
/************************************************************/
#include "types.h"
#include "ir.h"
#include "ir_defines.h"
#include "delay.h"

u8 IR_READ(u32 *address, u32 *command, u32 *toggle)    
{
    u32 data = 1;              
    u32 i, level;             
    delay_us(IR_T - IR_Q);          

    for(i = 0; i < 13; i++)            
    {
        level = IR_PIN;               
        if(!CHECK_EDGE(level, IR_T))   
            return 0;                  

        delay_us(IR_Q);               

        if(IR_PIN == 0)               
            data = (data << 1) | 1;     
        else                            
            data = (data << 1);         

        delay_us(IR_H);             
    }

    if(((data >> 12) & 1) != 1)       
        return 0;                      

    *toggle  = ((data >> 11) & 1);        
    *address = ((data >> 6) & 0x1F);    
    *command = (data & 0x3F);    
    return 1;                           
}

static u8 CHECK_EDGE(u32 level, u32 time_out)
{
    u32 t = 0;                 
    while(t < time_out)                
    {
        if(IR_PIN != level)            
            return 1;                  
        delay_us(STEP_TIME);              
        t += STEP_TIME;               
    }
    return 0;                 
}

static void CHECK_IDLE(void)
{
    unsigned int t = 0;                 

    while(t < 4000)                    
    {
        if(IR_PIN == 0)               
            t = 0;                     
        else                        
            t += STEP_TIME;              
        delay_us(STEP_TIME);              
    }
}
