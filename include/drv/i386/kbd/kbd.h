#ifndef _DRV_KBD_H_
#define _DRV_KBD_H_


/*
 * Keyboard Ports
 * On Motherboard Keyboard
 * and Keyboard Encoder.
 */
#define I386_KBD_ENCODER_PORT_READ  0x60
#define I386_KBD_ENCODER_PORT_WRITE 0x60

#define I386_KBD_ONBOARD_PORT_READ  0x64
#define I386_KBD_ONBOARD_PORT_WRITE 0x64


/*
 * Keyboard Status
 * register defintions
 */

#define OUTPUT_BUFFER_EMPTY 		0x0    //0
#define OUTPUT_BUFFER_FULL  		0x1    //1
#define INPUT_BUFFER_EMPTY  		0x0    //0
#define INPUT_BUFFER_FULL   		0x2    //10
#define SYSTEM_FLAG_SET_RESET 		0x0    //000
#define SYSTEM_FLAG_SELF_TEST 		0x4    //100
#define LAST_WRITE_DATA		  		0x0    //0000
#define LAST_WRITE_COMMAND    		0x8    //1000
#define KBD_LOCKED			  		0x0    //00000
#define KBD_UNLOCKED		  		0x10   //10000
#define KBD_AUX_BUFF_PS2_KBDATA 	0x0    //000000
#define KBD_AUX_BUFF_PS2_MOUSEDATA  0x20   //100000
#define KBD_AUX_BUFF_ATA_OK     	0x0    //000000
#define KBD_AUX_BUFF_ATA_TIMEOUT 	0x20   //100000
#define KBD_TIMEOUT_OK 			 	0x0    //0000000
#define KBD_TIMEOUT_TIME			0x40   //1000000
#define KBD_PARITY_ERROR_OK     	0x0    //00000000
#define KBD_PARITY_ERROR_LAST   	0x80   //10000000

/*
 * keyboard Encoder Commands
 */

#define KBD_ENCODER_CMD_SET_LED 	 						0xED
#define KBD_ENCODER_CMD_ECHO		 						0xEE
#define KBD_ENCODER_CMD_SET_SCANCODE 						0xF0
#define KBD_ENCODER_CMD_SEND_ID		 						0xF2
#define KBD_ENCODER_CMD_SET_REPEAT_RATE 					0xF3
#define KBD_ENCODER_CMD_ENABLE_KBD  						0xF4
#define KBD_ENCODER_CMD_RESET_WAIT_ENABLE 					0xF5
#define KBD_ENCODER_CMD_RESET_SCAN_KBD  					0xF6
#define KBD_ENCODER_PS2_CMD_SET_KEYS_AUTOREPEAT 			0xF7
#define KBD_ENCODER_PS2_CMD_SEND_MAKE_BREAK_CODE 			0xF8
#define KBD_ENCODER_CMD_GEN_MAKE_CODES 						0xF9
#define KBD_ENCODER_CMD_SET_AUTOREPEAT_MAKE 				0xFA
#define KBD_ENCODER_CMD_SINGLE_KEY_AUTOREPEAT 				0xFB
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_MAKE_BREAK_CODE 		0xFC
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_BREAKCODE 			0xFD
#define KBD_ENCODER_CMD_SEND_LAST_RESULT 					0xFE
#define KBD_ENCODER_CMD_RESET_KBD_SST 						0xFF




extern void init_kbd();

#endif