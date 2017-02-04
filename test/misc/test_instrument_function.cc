#include <stdio.h>

#define DUMP(func, call) printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)

/*
void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_exit(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
}
*/

/*
void __cyg_profile_func_enter(void* this_func, void* call_site) __attribute__((__no_instrument_function__));
void __cyg_profile_func_exit(void* this_func, void* call_site) __attribute__((__no_instrument_function__));
*/

int main()
{
        puts("Hello World!");
        return 0;
}

/*
void __cyg_profile_func_enter(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
        DUMP(this_func, call_site);
}
*/
