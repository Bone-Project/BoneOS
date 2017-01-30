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

 **   Amanuel Bogale <amanuel2> : start
 **/
 
 
#ifndef _ARCH_MM_PAGE_FRAME_H_
#define _ARCH_MM_PAGE_FRAME_H_

#define PAGE_SIZE 4096
#define PAGE_SHIFT 12
#define PAGE_FREE 1
#define PAGE_USED 0

extern int init_page_frame(multiboot_info_t *);

extern void *allocate_pages(size_t num);

extern void free_pages(void *first,size_t num);

#endif // _ARCH_MM_PAGE_FRAME_H_
