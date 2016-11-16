#ifndef _DRV_KBD_H_
#define _DRV_KBD_H_


/*PORTS*/
#define KBD_ENC_INPUT_BUF_REG 0x60
#define KBD_ENC_CMD_REG       0x60

#define KBD_CTRL_STATS_REG 0x64
#define KBD_CTRL_CMD_REG   0x64


/*STATUS*/

#define KBD_CTRL_STATS_MASK_OUT_BUF     0x1   //00000001
#define KBD_CTRL_STATS_MASK_IN_BUF         0x2   //00000010
#define KBD_CTRL_STATS_MASK_SYSTEM        0x4   //00000100
#define KBD_CTRL_STATS_MASK_CMD_DATA  0x8   //00001000
#define KBD_CTRL_STATS_MASK_LOCKED       0x10    //00010000
#define KBD_CTRL_STATS_MASK_AUX_BUF      0x20    //00100000
#define KBD_CTRL_STATS_MASK_TIMEOUT      0x40    //01000000
#define KBD_CTRL_STATS_MASK_PARITY          0x80    //10000000

/*ENCODER COMMANDS*/
#define KBD_ENCODER_CMD_SET_LED                                                            0xED
#define KBD_ENCODER_CMD_ECHO                                                                   0xEE
#define KBD_ENCODER_CMD_SET_SCANCODE                                              0xF0
#define KBD_ENCODER_CMD_SEND_ID                                                             0xF2
#define KBD_ENCODER_CMD_SET_REPEAT_RATE                                        0xF3
#define KBD_ENCODER_CMD_ENABLE_KBD                                                    0xF4
#define KBD_ENCODER_CMD_RESET_WAIT_ENABLE                                   0xF5
#define KBD_ENCODER_CMD_RESET_SCAN_KBD                                         0xF6
#define KBD_ENCODER_PS2_CMD_SET_KEYS_AUTOREPEAT                   0xF7
#define KBD_ENCODER_PS2_CMD_SEND_MAKE_BREAK_CODE              0xF8
#define KBD_ENCODER_CMD_GEN_MAKE_CODES                                        0xF9
#define KBD_ENCODER_CMD_SET_AUTOREPEAT_MAKE                             0xFA
#define KBD_ENCODER_CMD_SINGLE_KEY_AUTOREPEAT                         0xFB
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_MAKE_BREAK_CODE 0xFC
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_BREAKCODE               0xFD
#define KBD_ENCODER_CMD_SEND_LAST_RESULT                                    0xFE
#define KBD_ENCODER_CMD_RESET_KBD_SST                                            0xFF


/*CTRL COMMANDS*/
#define KBD_CTRL_CMD_SELF_TEST  0xAA

/*RETURN CODES*/
#define KBD_ENC_FAIL_BAT_TEST       0xFC



extern void init_kbd();

#endif