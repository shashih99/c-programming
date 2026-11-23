/* 09_preprocessor.c - #define, #undef, conditional compilation, predefined macros, #error
 * Try:  gcc 09_preprocessor.c -DDEBUG -DLEVEL=3     (define macros from the command line)
 *       gcc -E 09_preprocessor.c | tail -40          (see the preprocessed output)       */
#include <stdio.h>

#define PI 3.14159
#define APP_NAME "notes-demo"
#define BUFFER_SIZE 64

#ifndef LEVEL                    /* default if not given with -DLEVEL=n */
#define LEVEL 1
#endif

#if LEVEL < 0
#error "LEVEL must be >= 0"      /* stops compilation with this message */
#endif

#ifdef DEBUG
#define LOG(msg) fprintf(stderr, "[debug %s:%d] %s\n", __FILE__, __LINE__, msg)
#else
#define LOG(msg) ((void)0)       /* compiles to nothing */
#endif

int main(void)
{
    char buf[BUFFER_SIZE];
    snprintf(buf, sizeof buf, "%s v%d", APP_NAME, LEVEL);
    printf("%s, PI = %.5f, buf size = %d\n", buf, PI, BUFFER_SIZE);

    LOG("inside main");

#if LEVEL >= 3
    printf("LEVEL >= 3: verbose mode\n");
#elif LEVEL == 2
    printf("LEVEL == 2: normal mode\n");
#else
    printf("LEVEL <= 1: quiet mode\n");
#endif

#if defined(__linux__)
    printf("platform: Linux\n");
#elif defined(_WIN32)
    printf("platform: Windows\n");
#else
    printf("platform: other\n");
#endif

    printf("__FILE__ = %s, __LINE__ = %d, __func__ = %s\n", __FILE__, __LINE__, __func__);
    printf("__STDC_VERSION__ = %ldL\n", __STDC_VERSION__);
    printf("compiled on %s at %s\n", __DATE__, __TIME__);

#undef PI
#ifndef PI
    printf("PI is no longer defined after #undef\n");
#endif
    return 0;
}
