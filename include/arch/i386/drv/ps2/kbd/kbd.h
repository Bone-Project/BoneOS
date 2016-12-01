#ifndef _DRV_KBD_H_
#define _DRV_KBD_H_


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
#define KBD_ENCODER_CMD_SET_LED                       0xED
#define KBD_ENCODER_CMD_ECHO                          0xEE
#define KBD_ENCODER_CMD_SET_SCANCODE                  0xF0
#define KBD_ENCODER_CMD_SEND_ID                       0xF2
#define KBD_ENCODER_CMD_SET_REPEAT_RATE               0xF3
#define KBD_ENCODER_CMD_ENABLE_KBD                    0xF4
#define KBD_ENCODER_CMD_RESET_WAIT_ENABLE             0xF5
#define KBD_ENCODER_CMD_RESET_SCAN_KBD                0xF6
#define KBD_ENCODER_PS2_CMD_SET_KEYS_AUTOREPEAT       0xF7
#define KBD_ENCODER_PS2_CMD_SEND_MAKE_BREAK_CODE      0xF8
#define KBD_ENCODER_CMD_GEN_MAKE_CODES                0xF9
#define KBD_ENCODER_CMD_SET_AUTOREPEAT_MAKE           0xFA
#define KBD_ENCODER_CMD_SINGLE_KEY_AUTOREPEAT          0xFB
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_MAKE_BREAK_CODE 0xFC
#define KBD_ENCODER_CMD_SINGLE_KEY_GEN_BREAKCODE       0xFD
#define KBD_ENCODER_CMD_SEND_LAST_RESULT               0xFE
#define KBD_ENCODER_CMD_RESET_KBD_SST                  0xFF


/*CTRL COMMANDS*/
#define KBD_CTRL_CMD_SELF_TEST  0xAA

/*RETURN CODES*/
#define KBD_ENC_FAIL_BAT_TEST       0xFC

/*LED LIGHT*/
#define KBD_SCROLL_LED_ON 0x1
#define KBD_NUM_LED_ON        0x2
#define KBD_CAPS_LOCK_ON   0x4

/*KEYS*/
#define KBD_QWERTY_LEFT_SHIFT_PRESS 0x2A
#define KBD_QWERTY_RIGHT_SHIFT_PRESS 0x36
#define KBD_QWERTY_LEFT_SHIFT_RELEASE 170
#define KBD_QWERTY_RIGHT_SHIFT_RELEASE 182

#define KBD_QWERTY_CAPS_PRESS 0x3A
#define KBD_QWERTY_CAPS_RELEASE 186

#define KBD_QWERTY_ENTER_PRESS 0x1C
#define KBD_QWERTY_ENTER_RELEASE 156

extern int init_kbd();
extern int uninit_kbd();

#ifdef KBD_PRE
extern const char QWERTY_EN_NOSHIFT[] ;
extern const char QWERTY_EN_SHIFT[];
extern uint8_t kbd_ctrl_read_status_reg();
extern void kbd_ctrl_send_cmd(uint8_t cmd);
extern uint8_t kbd_enc_read_input_buf();
extern void kbd_enc_send_cmd(uint8_t cmd);
extern bool bat_test(void);
extern bool led_light(bool scroll, bool num, bool caps);
#endif

struct
_kbd_info
{
    struct 
    {
        bool num_lock;
        bool caps_lock;
        bool scroll_lock;
    }led;
    
    struct
    {
        bool shift;
        bool alt;
        bool ctrl;
    }spec_keys;
    
    struct
    {
        bool bat_test;
    }tests;
    
    struct
    {
        struct
        {
            bool (*bat_test)(void);
        }tests;
        
        struct
        {
            char (*key_press)(uint8_t scancode);
            void (*key_release)(uint8_t scancode);
        }key_ev;
        
    }routines;

    
    uint8_t kbd_enc_info;
    bool is_shift;
    bool is_enter;
    bool is_caps;
    uint32_t current_kbd_layout;
    char key;
    
};

extern struct _kbd_info kbd_info;
extern volatile bool initalized_ps2_kbd;
extern volatile bool status_ps2_kbd;

#endif