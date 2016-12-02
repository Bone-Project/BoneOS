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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <validate_char/validate_char.h>
#include <eat_front_whitespace/eat_front_whitespace.h>

/*
 * @function get_opt_count
 *  Returns the number of options
 *	including the command it self.
 *      
 *      @param s:
 *         Specified Command in
 *		   string format.
 *      @return {size_t} :
 *         Returns number of options.
 */
 
size_t get_opt_count(const char *s)
{ 
	const char *s_temp = eat_front_whitespace(s);
	size_t len=0;
	bool active = false; 
	while(*s_temp++)
	{ 
		if(active==false) 
		{
			 if(validate_char(*s_temp) == true)
			 {
			   active = true; 
			   len++;
			 }
	    }
	    else
	    	if(validate_char(*s_temp) == false) 
	    	  active = false;
	} 
  return len;
} 