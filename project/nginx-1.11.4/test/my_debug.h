#ifndef MY_DEBUG_LENKY_H
#define MY_DEBUG_LENKY_H

#include <stdio.h>

void enable_my_debug(void)  __attribute__((__no_instrument_function__));
void disable_my_debug(void) __attribute__((__no_instrument_function__));

int get_my_debug_flag(void)  __attribute__((__no_instrument_function__));
void set_ny_debug_flag(int flag) __attribute__((__no_instrument_function__));

void main_constructor(void) __attribute__((__no_instrument_function__, constructor));
void main_destructor(void)  __attribute__((__no_instrument_function__, destructor));

void __cyg_profile_func_enter(void*, void*) __attribute__((__no_instrument_function__));
void __cyg_profile_func_exit(void*, void*)  __attribute__((__no_instrument_function__));

#ifndef MY_DEBUG_MAIN
extern FILE* my_debug_fd;
#else
FILE *my_debug_fd = NULL;
#endif

// FILE *my_debug_fd;

#endif // MY_DEBUG_LENKY_H
