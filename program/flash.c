#include <msp430.h>
#include "3140_concur.h"


/* sets flash up to write
*  lock = 0
*  WRT = 1
*/
void writing_start() {
	FCTL3 = 0x0A500;
	FCTL1 = 0x0A540;
}

/* finish writing
*  lock = 1
*  WRT = 0
*/
void writing_end() {
	FCTL1 = 0x0A500;
	FCTL3 = 0x0A510;
}


/* flash_byte */
/* programs 1 byte (8 bits) into the flash memory */
void flash_byte(char *address, char byte) {
	writing_start();
	*address = byte;
	writing_end();
}

/* flash word */
/* programs 1 wor (16 bits) into the flash memory */
void flash_word(int *address, int word) {
	writing_start();
	*address = word;
	writing_end();
}

/* flash erase */
/* erases 1 segment of flash memory */
void flash_erase(int *address) {
	FCTL3 = 0x0A500;
	FCTL1 = 0x0A502;
	*address = 0;
	writing_end();
}

void erase_range(char *address, int bytes){
	FCTL3 = 0x0A500;
	FCTL1 = 0x0A502;
	int i=0;
	while(i<bytes){
		*(address+i) = 0x00;
		i++;
	}
	writing_end();
}


