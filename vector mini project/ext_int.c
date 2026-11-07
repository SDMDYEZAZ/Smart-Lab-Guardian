/**************************************************************************/
/* File Name : ext_int.c                                                  */
/* Description : Contains the function definitions of external interrupts */
/* Controller : LPC2129/LPC2148                                           */
/**************************************************************************/

#include <LPC21XX.H>
#include "types.h"
#include "ext_int.h"
#include "ext_int_defines.h"

/* Function pointers for user-defined external interrupt callbacks */
void (*EINT0_FUN)(void);
void (*EINT1_FUN)(void);
void (*EINT2_FUN)(void);
void (*EINT3_FUN)(void);

/*
 * Function Name : EINT0_INIT
 * Description   : Configures EINT0 as a falling-edge triggered interrupt 
                   and enables its corresponding VIC interrupt channel.
 */
 
void EINT0_INIT(void)
{
	  /* Configure P0.1 as EINT0 function */
    PINSEL0 &= ~EINT0_PIN_FUNC;
    PINSEL0 |= (1 << 3);

	  /* Configure EINT0 for edge-sensitive falling-edge triggering */
    EXTMODE |= (1 << 0);
    EXTPOLAR &= ~(1 << 0);

  	/* Configure EINT0 interrupt as an IRQ interrupt */
    VICIntSelect &= ~(1 << EINT0_VIC_CHNO);
	
	  /* Enable EINT0 interrupt in the VIC */
    VICIntEnable |= (1 << EINT0_VIC_CHNO);

	  /* Assign EINT0 to VIC vector slot 0 */
    VICVectCntl0 = 0x20 | EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)EINT0_ISR;
}

/*
 * Function Name : EINT1_INIT
 * Description   : Configures EINT1 as a falling-edge triggered interrupt 
                   and enables its corresponding VIC interrupt channel.
 */

void EINT1_INIT(void)
{
	  /* Configure P0.3 as EINT1 function */
    PINSEL0 &= ~EINT1_PIN_FUNC;
    PINSEL0 |= (1 << 7);

	  /* Configure EINT1 for edge-sensitive falling-edge triggering */
    EXTMODE |= (1 << 1);
    EXTPOLAR &= ~(1 << 1);
    
	  /* Configure EINT1 interrupt as an IRQ interrupt */
    VICIntSelect &= ~(1 << EINT1_VIC_CHNO);
	
	  /* Enable EINT1 interrupt in the VIC */
    VICIntEnable |= (1 << EINT1_VIC_CHNO);

	  /* Assign EINT1 to VIC vector slot 1 */
    VICVectCntl1 = 0x20 | EINT1_VIC_CHNO;
    VICVectAddr1 = (u32)EINT1_ISR;
}

/*
 * Function Name : EINT2_INIT
 * Description   : Configures EINT2 as a falling-edge triggered interrupt 
                   and enables its corresponding VIC interrupt channel.
 */

void EINT2_INIT(void)
{
	  /* Configure P0.7 as EINT2 function */
    PINSEL0 &= ~EINT2_PIN_FUNC;
    PINSEL0 |= (1 << 15);

	  /* Configure EINT2 for edge-sensitive falling-edge triggering */
    EXTMODE |= (1 << 2);
    EXTPOLAR &= ~(1 << 2);

	  /* Configure EINT2 interrupt as an IRQ interrupt */
    VICIntSelect &= ~(1 << EINT2_VIC_CHNO);
	
	  /* Enable EINT2 interrupt in the VIC */
    VICIntEnable |= (1 << EINT2_VIC_CHNO);

	  /* Assign EINT2 to VIC vector slot 2 */
    VICVectCntl2 = 0x20 | EINT2_VIC_CHNO;
    VICVectAddr2 = (u32)EINT2_ISR;
}

/*
 * Function Name : EINT3_INIT
 * Description   : Configures EINT3 as a falling-edge triggered interrupt 
                   and enables its corresponding VIC interrupt channel.
 */

void EINT3_INIT(void)
{
	  /* Configure P0.9 as EINT3 function */
    PINSEL0 &= ~EINT3_PIN_FUNC;
    PINSEL0 |= (1 << 19);

	  /* Configure EINT3 for edge-sensitive falling-edge triggering */
    EXTMODE |= (1 << 3);
    EXTPOLAR &= ~(1 << 3);

	  /* Configure EINT3 interrupt as an IRQ interrupt */
    VICIntSelect &= ~(1 << EINT3_VIC_CHNO);
	
	  /* Enable EINT3 interrupt in the VIC */
    VICIntEnable |= (1 << EINT3_VIC_CHNO);
   
	  /* Assign EINT3 to VIC vector slot 3 */
    VICVectCntl3 = 0x20 | EINT3_VIC_CHNO;
    VICVectAddr3 = (u32)EINT3_ISR;
}

/*
 * Function Name : EINT0_ISR
 * Description   : Handles the EINT0 interrupt request and executes 
                   the registered callback function.
 */

void EINT0_ISR(void) __irq
{
	  /* Clear EINT0 interrupt flag */
    EXTINT = (1 << 0);

	  /* Execute callback function if registered */
    if(EINT0_FUN != 0)
        EINT0_FUN();
    
		/* Signal completion of interrupt servicing to the VIC */
    VICVectAddr = 0;
}

/*
 * Function Name : EINT1_ISR
 * Description   : Handles the EINT1 interrupt request and executes
                   the registered callback function.
 */

void EINT1_ISR(void) __irq
{
	  /* Clear EINT1 interrupt flag */
    EXTINT = (1 << 1);

	  /* Execute callback function if registered */
    if(EINT1_FUN != 0)
		{
        EINT1_FUN();
		}

		/* Signal completion of interrupt servicing to the VIC */
    VICVectAddr = 0;
}

/*
 * Function Name : EINT2_ISR
 * Description   : Handles the EINT2 interrupt request and executes 
                   the registered callback function.
 */

void EINT2_ISR(void) __irq
{
	  /* Clear EINT2 interrupt flag */
    EXTINT = (1 << 2);

	  /* Execute callback function if registered */
    if(EINT2_FUN != 0)
		{
        EINT2_FUN();
		}

		/* Signal completion of interrupt servicing to the VIC */
    VICVectAddr = 0;
}

/*
 * Function Name : EINT3_ISR
 * Description   : Handles the EINT3 interrupt request and execute 
                   the registered callback function.
 */

void EINT3_ISR(void) __irq
{
	  /* Clear EINT3 interrupt flag */
    EXTINT = (1 << 3);

	  /* Execute callback function if registered */
    if(EINT3_FUN != 0)
		{
        EINT3_FUN();
		}

	  /* Signal completion of interrupt servicing to the VIC */
    VICVectAddr = 0;
}
