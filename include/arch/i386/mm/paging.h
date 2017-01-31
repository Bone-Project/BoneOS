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

#ifndef _ARCH_MM_PAGING_H_
#define _ARCH_MM_PAGING_H_

#include <stdint.h>
#include <mm/page_frame.h>
#include <mm/pmm_util.h>

typedef uint32_t pte_t;
typedef uint32_t pde_t;


extern int init_paging();

#endif _ARCH_MM_PAGING_H_
