/*------------------------------------------------------------
 * Example radio "send" application
 *   Sends packets with a data payload in an infinite loop
 *----------------------------------------------------------*/

#include "bsp.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include "3140_concur.h"
#include <string.h>

/* Useful #defines */
#define RED_LED 		0x01
#define GREEN_LED  			0x02

uint8_t id = 0x01;
uint8_t num = 0x01;
char messages[];

/* Function prototypes */
void sleep(unsigned int count);

void relay_msg(mrfiPacket_t* packet);

/* Main function for transmit application */
void main(void) {
	/* Set a filter address for packets received by the radio
	 *   This should match the "destination" address of
	 *   the packets sent by the transmitter. */
	uint8_t channel[] = {0x11,0x11,0x11,0x11};

	//erase_range(((char*) 0), 4096);
	messages = new char[4096];

	/* Filter setup return value: success or failure */
	unsigned char status;

	/* Perform board-specific initialization */
	BSP_Init();

	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();

	status = MRFI_SetRxAddrFilter(channel);
	MRFI_EnableRxAddrFilter();
	if( status != 0) {
		P1OUT = RED_LED | GREEN_LED;
		while(1);
	}

	/* Set red LED to output */
	P1DIR = RED_LED | GREEN_LED;
	P1OUT = RED_LED | GREEN_LED;

	__bis_SR_register(GIE);

	/* Turn on the radio receiver */
	MRFI_RxOn();

	/* Main (infinite) transmit loop */
	while(1){
		/* Construct a packet to send over the radio.
		 * 
		 *  Packet frame structure:
		 *  ---------------------------------------------------
		 *  | Length (1B) | Dest (4B) | Source (4B) | Payload |
		 *  ---------------------------------------------------
		 */
		mrfiPacket_t 	packet;
		char msg[] = "ECE3140 rocks!\r\n"; 

		/* First byte of packet frame holds message length in bytes */
		packet.frame[0] = strlen(msg) + 8;	/* Includes 8-byte address header */

		/* Next 8 bytes are addresses, 4 each for source and dest. */
		packet.frame[1] = 0x11;		/* Channel */
		packet.frame[2] = 0x11;
		packet.frame[3] = 0x11;
		packet.frame[4] = 0x11;

		packet.frame[5] = 0x03;		/* Destination */
		packet.frame[6] = id;		/* Source */
		packet.frame[7]	= 0x01;		/* Distance */
		packet.frame[8] = num;		/* Message Number */

		num = num + 0x01;

		/* Remaining bytes are the message/data payload */
		strcpy( (char *) &packet.frame[9] , msg );

		/* Transmit the packet over the radio */
		MRFI_Transmit(&packet , MRFI_TX_TYPE_FORCED);

		/* Toggle red & green LED after transmitting, then wait a while */
		P1OUT ^= RED_LED | GREEN_LED;
		sleep(60000);
	}
}

/* Function to execute upon receiving a packet
 *   Called by the driver when new packet arrives */
void MRFI_RxCompleteISR(void) {
	/* Read the received data packet */
	mrfiPacket_t	packet;
	MRFI_Receive(&packet);

	/* do not accept your own messages */
	if(packet.frame[6]==id){
		return;
	}

	/* Check to see the id of this message */
	//if not already sent, relay
	unsigned int hash = packet.frame[6];
	hash = hash << 8;
	hash = hash + packet.frame[8];
	if(0x00 == *((char*) hash)){
		/* If for you, toggle green
		 * If to be relayed, toggle red*/
		flash_byte((char*) hash, 0x01);

		if(packet.frame[5]==id){
			P1OUT ^= GREEN_LED;
		}
		else if(packet.frame[7]<=2){
			relay_msg(&packet);
		}

	}

}

void relay_msg(mrfiPacket_t* packet){

	packet->frame[7] = packet->frame[7] + 0x01;

	MRFI_Transmit(packet , MRFI_TX_TYPE_FORCED);
}

/* Parameterized "sleep" helper function */
void sleep(unsigned int count) {
	int i;
	for (i = 0; i < 10; i++) {
		while(count > 0) {
			count--;
			__no_operation();
		}
	}
}
