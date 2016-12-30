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
 **/  

/*
 * @function strstr:
 *    Returns substring + rest of
 *    string , from the string.
 *
 *        @param __str (char*):
 *           Specified string
 *           to find substring from.
 *      
 *        @param __substr (char*):
 *           the Substring to be searched 
 *           for.

 *        @return (str_t):
 *           Returns the substring + rest
 *           of string.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <strstr/strstr.h>
#include <strlen/strlen.h>
#include <strcmp/strcmp.h>
#include <memmove/memmove.h>

#include <stdio/stdio.h>

str_t strstr(char* __str, char* __substr)
{
    size_t strlen__substr = strlen(__substr);
    size_t strlen__str = strlen(__str);
    char __temp[strlen__substr];
    str_t __return_str;
    int __start_index=0;
    bool __found=false;
    
    int index=0;
    while(__str[index])
    {
        if(__str[index] == __substr[0])
        {
            int i=0;
            for(; __substr[i]; i++)
                __temp[i] = __str[i+index];
            __temp[i] = '\0';
            
            if(strcmp(__temp,__substr)==0)
            {
                __start_index = (i+index)-strlen__substr;
                __found=true;
                for(int i=0; i<200;i++) __return_str.str[i]=0;
                 for(uint32_t i=__start_index,j=0; i<strlen__str;i++,j++)
                     __return_str.str[j]=__str[i];
            }
            index++;
        }
        else index++;
    }
    
    if(__found==false)
        __return_str.str[0] = 0;
    return __return_str;
}





