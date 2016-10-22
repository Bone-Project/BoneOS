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

#include <include/libc/i386/stdio/itoa/itoa.h>

/*
 * @function __itoa:
 *    __itoa is itoa version
 *    #2 which contains the base
 *    on which you inputed.
 *
 *      @param i:
 *          integer to convert
 *      @param base:
 *          base of the integer to convert
 *      @param buf:
 *          The result will be inserted
 *          in this character buffer
 */

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7',
                 '8','9','A','B','C','D','E','F'};
void __itoa(unsigned i,unsigned base,char* buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;

    if (i == 0 || base > 16)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    while (i != 0)
    {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    top=pos--;
    for (opos=0; opos<top; pos--,opos++)
        buf[opos] = tbuf[pos];
    buf[opos] = 0;
}

/*
 * @function itoa:
 *     itoa is the First version
 *     of itoa functions. This
 *     does not require the base.
 *     
 *       @param val:
 *           integer to convert to
 *           a character buffer.
 *          
 *       @return {Character Buffer}:
 *          Returns the character buffer
 *          resulted from the translation
 *          from specified integer
 *     
 */
char *itoa(int val)

{
    uint8_t *ptr;
    static uint8_t buffer[16];
    ptr = buffer + sizeof(buffer);
    *--ptr = '\0';

    if (val == 0)
    {
        *--ptr = '0';
    }
    else while (val != 0)
    {
        *--ptr = (val % 10) + '0';
        val = val / 10;
    }
    return((char*)ptr);
}
