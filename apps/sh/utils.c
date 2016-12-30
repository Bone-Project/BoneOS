/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **   Amanuel Bogale <amanuel2> : start
 **/
 
 #include <str_t.h>
 #include <stdbool.h>
 #include <unistd/unistd.h>
 #include <string/string.h>
 
int termcmp(const char* cmd, const char* value)
{
  size_t num_opts_cmp = get_opt_count(value);
  str_t opts_cmp[num_opts_cmp];
  get_opt(value,opts_cmp);   
  if(strcmp(opts_cmp[0].str,cmd)==0)
    return 0;
  return 1;  
}

bool is_contain_equal(char* s)
{
  while(*s)
    if(*s++ == '=')
        return true;
  return false;    
}

str_t term_assignment_return_variable(str_t s)
{
  int counter = 0;
  str_t __return;
  for(int i=0; i<200;i++) __return.str[i]=0;
  
  while(s.str[counter] != '=') {
    __return.str[counter]+=s.str[counter];
    counter++;
  }
  return __return;
}

str_t term_assignment_return_value(str_t s)
{
  int counter=0;
  int self_index=0;
  str_t __return;
  for(int i=0; i<200;i++) __return.str[i]=0;
  
  while(s.str[counter++] != '=');
  for(; s.str[counter]; counter++)
  {
     __return.str[self_index++]+=s.str[counter];
  }
  
  return __return;
}

 


