#ifndef  _APPS_TERM_TERMINAL_H_
#define _APPS_TERM_TERMINAL_H_

struct cmd_opt
{
  char* help;
  char* cmd_opt_name;
  int(*handler)(void);
};

struct cmd
{
  char* command_name;
  char*  usage;
  char*  help;
  struct cmd_opt** cmd_opts;
  int(*handler)(void);
};

struct typed_cmd
{
  char* value;
};

extern void init_terminal();

#endif /*_APPS_TERM_TERMINAL_H_*/