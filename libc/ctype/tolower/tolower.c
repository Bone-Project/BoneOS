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
 **  @main_author : Muhammad Rifqi Priyo Susanto
 **  
 **  @contributors:

 **     Muhammad Rifqi Priyo Susanto <srifqi> : start
 **/ 

/*
 * @function tolower:
 *      Converts specified character
 *      to a lower case caracter
 *
 *         @param c:
 *              Specified Character
 *
 *          @return int:
 *                Returns the lowercase
 *                of the character specified.  
 */

int tolower(int c)
{
   if(c>=65 && c<=90)
        return(c+32);
   else
        return c; 
}



