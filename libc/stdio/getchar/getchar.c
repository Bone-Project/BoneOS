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
#include <stdio/stdio.h>

volatile bool __get_char_set=false; 
volatile char __get_char_chr = 0;

/*
 * @function getchar:
 *
 *      @param void:
 *          No Parameters given
 *          outlaws parameters in C.
 *          **explicitly**
 *
 *      @return (int):
 *          Returns the single character typed
 *
 */
 

int getchar(void)
{
    /*TODO*/
    while(__get_char_set==false);
    __get_char_set = false;
    return __get_char_chr; //Getchar not implemented yet
}


