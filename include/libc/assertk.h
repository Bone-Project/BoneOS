#ifndef  _LIBC_ASSERT_H_
#define _LIBC_ASSERT_H_

#include <misc/asm_util.h>
#include "stdio/printk/printk.h"

/* 
 * @function assertk:
 *   Checks if Expression is true
 *   if not infinite halt.
 */
#define assertk(EXPRESSION)  \
              if(!EXPRESSION)  \
              {  \
                  printk("ERROR : {FILE : %s , LINE : %d}", __FILE__ , __LINE__); \
                  while(1);  \
                  hlt(); \
              } 

/* 
 * @function assertkm:
 *   Checks if Expression is true
 *   if not infinite halt and prints
 *   specified message
 */
 
#define assertkm(EXPRESSION,MSG)  \
              if(!EXPRESSION)  \
              {  \
                   printk("ERROR : {FILE : %s , LINE : %d} ERROR MSG : %s" , __FILE__ , __LINE__, MSG); \
                   while(1);  \
                   hlt(); \
              }   


/* 
 * @function assertsok:
 *   Checks if Expression is equal
 *   to STATUS_OK if not infinite loop. 
 */
  
#define assertsok(EXPRESSION)  \
             if(EXPRESSION != STATUS_OK)  \
             {  \
                printk("STATUS_OK_ERROR : {FILE : %s , LINE : %d}" , __FILE__ , __LINE__); \
                while(1);  \
                hlt(); \
             }   

/* 
 * @function assertsokms:
 *   Checks if Expression is equal
 *   to STATUS_OK if not infinite loop
 *   and print message.
 */
 
#define assertsokms(EXPRESSION,MSG)  \
            if(EXPRESSION != STATUS_OK)  \
            {  \
                printk("STATUS_OK_ERROR : {FILE : %s , LINE : %d} ERROR MSG : %s" , __FILE__ , __LINE__, MSG); \
                while(1);  \
                hlt(); \
            }       
/* 
 * @function assertsv:
 *   Checks if Expression is equal
 *   to STATUS_VALID if not infinite loop.
 */                
#define assertsv(EXPRESSION)  \
          if(EXPRESSION != STATUS_VALID)  \
          {  \
              printk("STATUS_VALID_ERROR : {FILE : %s , LINE : %d}" , __FILE__ , __LINE__); \
              while(1);  \
              hlt(); \
          }   
/* 
 * @function assertsvm:
 *   Checks if Expression is equal
 *   to STATUS_VALID if not infinite loop
 *   and print message.
 */                  
#define assertsvm(EXPRESSION,MSG)  \
            if(EXPRESSION != STATUS_VALID)  \
            {  \
                printk("STATUS_VALID_ERROR : {FILE : %s , LINE : %d} ERROR MSG : %s" , __FILE__ , __LINE__, MSG); \
                while(1);  \
                hlt(); \
            }

/* 
 * @function assertdok:
 *   Checks if Expression is equal
 *   to STATUS_DRIVER_OK if not infinite loop
 *   and print message.
 */   
#define assertdok(EXPRESSION)  \
            if(EXPRESSION != STATUS_DRIVER_OK)  \
            {  \
                printk("STATUS_DRIVER_OK : {FILE : %s , LINE : %d}" , __FILE__ , __LINE__); \
                while(1);  \
                hlt(); \
            }
            
/* 
 * @function assertdokm:
 *   Checks if Expression is equal
 *   to STATUS_DRIVER_OK if not infinite loop
 *   and print message.
 */               
            
#define assertdokm(EXPRESSION,MSG)  \
            if(EXPRESSION != STATUS_DRIVER_OK)  \
            {  \
                printk("STATUS_DRIVER_OK : {FILE : %s , LINE : %d} ERROR MSG : %s" , __FILE__ , __LINE__, MSG); \
                while(1);  \
                hlt(); \
            }
            

#endif /*_LIBC_ASSERT_H_*/ 



