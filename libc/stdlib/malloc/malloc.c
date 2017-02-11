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
 **  @main_author : Ashish Ahuja
 **
 **  @contributors:

 **     Ashish Ahuja <Fortunate-MAN> : start
 **/

 #include <arch/i386/mm/pafe_frame.h>

 uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr) {
    /* Pages are aligned to 4K, or 0x1000 */
    if (align == 1 && (free_mem_start & 0xFFFFF000)) {
        free_mem_start &= 0xFFFFF000;
        free_mem_start += 0x1000;
    }
    /* Save also the physical address */
    if (phys_addr) *phys_addr = free_mem_start;

    uint32_t ret = free_mem_start;
    free_mem_start += size; /* Remember to increment the pointer */
    return &ret;
}
