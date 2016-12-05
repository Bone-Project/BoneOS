#ifndef _LIBC_UNISTD_GETOPT_H_
#define _LIBC_UNISTD_GETOPT_H_

typedef 
struct
{
	char str[200];
}str_t;


extern void get_opt(const char* s, str_t str_p[]);

#endif /*_LIBC_UNISTD_GETOPT_H_*/