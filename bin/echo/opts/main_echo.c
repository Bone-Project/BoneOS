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

 **     Amanuel Bogale <amanuel2> : start
 **     Semaphore: Added comments
 **/  
 
#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <echo/echo.h>

int main_echo_opt_handler(char *cmd) //Main handler for the echo command
{
   size_t num_opts = get_opt_count(cmd); //Get arg count from cmd 
   str_t opts[num_opts]; 
   get_opt(cmd,opts);
   
   char opts_one_key[strlen(opts[1].str)]; //
   
   for(int i=0; opts_one_key[i]; i++) opts_one_key[i] = 0;
   
   if(strcmp(opts[1].str , "--help")==0) //Search string in opts[1] for --help
      printk(cmd_echo.help); //Print help for echo
   else if(num_opts >= 2)
   {
    /* 
    Bellow starts a nest hell, have fun reading it
    
    note: this a joke, calm down.
    */
    size_t InputLength = (strlen(opts[1].str)-1); //Moving this up here will make it faster, and possibly easier to read
      if(opts[1].str[0] == '\'' && opts[num_opts-1].str[InputLength] == '\'') //if Input starts and ends with a single quote
      { //First paramater is a string that starts and ends with single quotes
          for(size_t i=1; i<num_opts; i++)
          {
            for(size_t j=0; opts[i].str[j]; j++)
            {
              if(i==1 && j==0) j++;
              if(i==(num_opts-1) && j == (InputLength) )
              { 
                printk("\n");  
                return STATUS_OK;
              }
               printk("%c" , opts[i].str[j]);
            }
            printk(" ");
          }
          return STATUS_OK;   
      }
      else if(opts[1].str[0] == '\"' && opts[num_opts-1].str[InputLength] == '\"') //If input starts and ends with double quotes
      { //first paramater is a string with double quotes
        for(size_t i=1; i<num_opts; i++)
          {
            for(size_t j=0; opts[i].str[j]; j++)
            {
              if(i==1 && j==0) j++;
              if(i==(num_opts-1) && j == (InputLength) )
              { 
                printk("\n");  
                return STATUS_OK;
              }
               printk("%c" , opts[i].str[j]);
            }
            printk(" ");
          }
      }
     for(size_t i=1; i<num_opts; i++)
       printk("%s " , opts[i].str);
     printk("\n");
   }
   else
      printk(cmd_echo.invalid_use_msg); //Print the error message for echo
    
   return STATUS_OK;
}






