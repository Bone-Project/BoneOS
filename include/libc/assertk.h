#ifndef  _LIBC_ASSERT_H_
#define _LIBC_ASSERT_H_

#include "misc/asm_util.h"
#include "stdio/printk/printk.h"

  #define assertk(EXPRESSION)  \
                if(!EXPRESSION)  \
                {  \
                    printk("ERROR : {FILE : %s , LINE : %d}", __FILE__ , __LINE__); \
                    while(1)  \
                       hlt(); \
                } 

 #define assertkm(EXPRESSION,MSG)  \
                if(!EXPRESSION)  \
                {  \
                    printk("ERROR : {FILE : %s , LINE : %d} ERROR MSG : %s" , __FILE__ , __LINE__, MSG); \
                    while(1)  \
                       hlt(); \
                }   

#endif /*_LIBC_ASSERT_H_*/ 
