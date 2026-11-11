/***************************************************************/
/* File Name : defines.h                                       */
/* Description : Bit manipulation macros for embedded systems. */
/* Controller : LPC2129/LPC2148                                */
/***************************************************************/

/*
 * Macro Name : WRITEBYTE
 * Description : Writes an 8-bit value at the specified bit position
 *               without modifying the remaining bits.
 * Parameters  : WORD     - Target register or variable
 *               STARTBIT - Starting bit position
 *               BYTE     - 8-bit data to be written
 */
 
#define WRITEBYTE(WORD, STARTBIT, BYTE) \
        WORD = ((WORD & ~ (0xFF << STARTBIT)) | (BYTE << STARTBIT))
				
/*
 * Macro Name : WRITENIBBLE
 * Description : Writes a 4-bit value at the specified bit position
 *               without modifying the remaining bits.
 * Parameters  : WORD     - Target register or variable
 *               STARTBIT - Starting bit position
 *               NIBBLE   - 4-bit data to be written
 */

#define WRITENIBBLE(WORD, STARTBIT, NIBBLE) \
				WORD = ((WORD & ~ (0XF << STARTBIT)) | (NIBBLE << STARTBIT))

/*
 * Macro Name : READNIBBLE
 * Description : Reads a 4-bit value from the specified nibble position.
 * Parameters  : WORD   - Source register or variable
 *               NIBBLE - Starting bit position
 */
 
#define READNIBBLE(WORD, NIBBLE) \
				((WORD >> NIBBLE)& 0XF)

/*
 * Macro Name : READBIT
 * Description : Reads the status of a specified bit.
 * Parameters  : WORD - Source register or variable
 *               BIT  - Bit position
 */
 
#define READBIT(WORD, BIT) \
				((WORD >> BIT) & 1)

/*
 * Macro Name : SETBIT
 * Description : Sets the specified bit to logic HIGH (1).
 * Parameters  : WORD - Target register or variable
 *               BIT  - Bit position
 */
 
#define SETBIT(WORD, BIT) \
				(WORD | = (1 << BIT))
