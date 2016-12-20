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
#include <stdarg.h>
#include <drv/ps2/kbd/kbd.h>
#include <libc/stdio/scank/scank.h>
#include <libc/stdlib/atoi/atoi.h>
#include <libc/stdlib/strtoi/strtoi.h>
#include <libc/string/strcpy/strcpy.h>
#include <misc/asm_util.h>

volatile uint32_t index_scank;
volatile bool active_scank;
volatile bool print_scank;
volatile char buffer_scank[4096];
volatile int LENGTH_INPUT=0;
volatile bool __backspace_count_active=false;

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
    return 0; //Getchar not implemented yet
}

