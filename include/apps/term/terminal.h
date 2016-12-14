#ifndef _APPS_TERM_TERMINAL_H_
#define _APPS_TERM_TERMINAL_H_

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

extern void init_terminal();
extern struct cmd_t *cmds[];

extern volatile struct typed_cmd cmd_active;

#endif /*_APPS_TERM_TERMINAL_H_*/

