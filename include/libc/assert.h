#ifndef  _LIBC_ASSERT_H_
#define _LIBC_ASSERT_H_

  #define assert(EXPRESSION) \
                if(!EXPRESSION)\
                {\
                    printk("ASSERT FAIL");\
                    while(1);\
                }\

#endif /*_LIBC_ASSERT_H_*/ 