/*********************************************************************************/
/* File Name   : ext_int.h                                                       */
/* Description : Contains the function prototypes and external callback function */
/*               pointer declarations for external interrupt operations.         */
/* Controller  : LPC2129 / LPC2148                                               */   
/*********************************************************************************/

/* External interrupt initialization function prototypes */
void EINT0_INIT(void);
void EINT1_INIT(void);
void EINT2_INIT(void);
void EINT3_INIT(void);

/* External interrupt service routine prototypes */
void EINT0_ISR(void) __irq;
void EINT1_ISR(void) __irq;
void EINT2_ISR(void) __irq;
void EINT3_ISR(void) __irq;

/* External declarations of callback function pointers */
extern void (*EINT0_FUN)(void);
extern void (*EINT1_FUN)(void);
extern void (*EINT2_FUN)(void);
extern void (*EINT3_FUN)(void);

