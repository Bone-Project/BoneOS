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
 * @function strtoi:
 *        This function converts
 *         a string to an integer
 *
 *      @param s:
 *            String to be converted
 *
 *      @param ret_end:
 *            Pass a pointer to a char *
 *            to have it set to point to
 *            the character after the last
 *            character parsed.
 *
 *      @param base:
 *            Pass the base of the number.
 *            For example,
 *              2 for binary,
 *              8 for octal,
 *              10 for decinal,
 *              16 for hexadecimal
 *            Any number in the range 2 to 16
 *            inclusive is valid.
 *
 *      @param (int):
 *             Returns the parsed integer.
 *
 */


int strtoi(char const *s, char **ret_end, int base)
{
	// Eat whitespace
	while (*s == '\n' || *s == '\t' || *s == ' ')
		++s;

	// Multiply by 1 at the end, unless...
	int sign = 1;
	if (*s == '-') {
		// It begins with -
		// Multiply by -1 at the end
		sign = -1;

		// Skip the -
		++s;
	}

	int n = 0;
	int d;
	while (1) {
		if (*s >= '0' && *s <= '9') {
			// Hex, binary, or octal
			d = *s++ - '0';
		} else if (*s >= 'A' && *s <= 'F') {
			// Uppercase hex
			d = 10 + (*s++ - 'A');
		} else if (*s >= 'a' && *s <= 'f') {
			// Lowercase hex
			d = 10 + (*s++ - 'a');
		} else {
			// Not a valid number character or null terminator
			break;
		}

		// If digit is outside valid range for base, then done
		if (d >= base)
			break;

		// Accumulate digit
		n = n * base + d;
	}

	// if the caller passed a pointer to a char pointer
	// then assign a pointer to where we stopped to it
	if (ret_end)
		*ret_end = (char*)s;

	return n * sign;
}




