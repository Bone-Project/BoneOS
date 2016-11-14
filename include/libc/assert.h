#ifndef  _LIBC_ASSERT_H_
#define _LIBC_ASSERT_H_

  #define assertk(EXPRESSION)  \
                if(!EXPRESSION)  \
                {  \
                    printk("ERROR : {FILE : %d , LINE : %d}", __FILE__ , __LINE__); \
                    while(1)  \
                       halt(); \
                }  \

#endif /*_LIBC_ASSERT_H_*/ 