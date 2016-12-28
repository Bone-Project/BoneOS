#ifndef _APPS_TERM_TERMINAL_H_
#define _APPS_TERM_TERMINAL_H_

#include <stddef.h>
#include <stdint.h>

typedef enum 
{
  ROOT,
  USER
}exec_prv;

struct cmd_opt_t
{
  char* help;
  char* cmd_opt_name;
  char* invalid_use_msg;
  int(*handler)(char* cmd);
};

struct cmd_t
{
  char*  name;
  char*  usage;
  char*  help;
  char*  invalid_use_msg;
  exec_prv privilege; 
  struct cmd_opt_t** cmd_opts;
  int(*handler)(char* cmd);
};

struct typed_cmd
{
  char* value;
};

#define CMD_CLEAR_INDEX 0
#define CMD_BONEOS_LOGO_INDEX 1
#define CMD_HELP_INDEX 2
#define CMD_SLEEP_INDEX 3
#define CMD_ECHO_INDEX 4
#define CMD_CURSOR_INDEX 5
#define CMD_REBOOT_INDEX 6
#define CMD_POWEROFF_INDEX 7
#define CMD_BONESHELL_INDEX 8

extern void init_terminal();
extern struct cmd_t *cmds[];

extern volatile struct typed_cmd cmd_active;
extern volatile uint32_t cmd_active_index;
volatile uint32_t shell_instance_cnt;

#endif /*_APPS_TERM_TERMINAL_H_*/



