#ifndef  _APPS_TERM_VALUES_H_
#define _APPS_TERM_VALUES_H_

#include <str_t.h>  


extern char* VAR_USER;
extern char* VAR_PWD;

struct pair_t
{
  char key[200];
  char val[200];
};

struct values
{
  int index;
  struct pair_t pairs[];
};

extern struct values __values;

#endif /*_APPS_TERM_VALUES_H_*/

