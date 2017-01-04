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
 * @function eat_front_whitespace
 *   Eats the whitespace at beggining
 *	 from string
 *      
 *      @param s:
 *         Specified String.
 *      @return {const char*} :
 *         Returns updated string.
 */
 
const char* eat_front_whitespace(const char*s)
{ 
	while((*s=='\t') || (*s=='\n') || (*s == ' '))
	  s++; 
    return s;
}





