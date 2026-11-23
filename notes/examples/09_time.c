/* 09_time.c - <time.h>: time, localtime, gmtime, strftime, mktime, difftime, clock */
#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t now = time(NULL);                        /* seconds since 1970-01-01 00:00 UTC */
    printf("time(NULL)  = %lld seconds since the epoch\n", (long long)now);

    struct tm *local = localtime(&now);             /* broken-down local time */
    printf("struct tm   : year=%d month=%d day=%d %02d:%02d:%02d weekday=%d yearday=%d\n",
           local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
           local->tm_hour, local->tm_min, local->tm_sec, local->tm_wday, local->tm_yday);

    char buf[64];
    strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S", local);
    printf("strftime    : %s\n", buf);
    strftime(buf, sizeof buf, "%A, %d %B %Y", local);
    printf("strftime    : %s\n", buf);

    strftime(buf, sizeof buf, "%Y-%m-%d %H:%M:%S UTC", gmtime(&now));
    printf("gmtime      : %s\n", buf);

    printf("ctime       : %s", ctime(&now));        /* includes its own '\n' */

    /* date arithmetic with mktime: 100 days from now (mktime normalises tm_mday) */
    struct tm later = *local;                       /* copy: localtime's buffer is shared */
    later.tm_mday += 100;
    time_t t_later = mktime(&later);
    strftime(buf, sizeof buf, "%Y-%m-%d", &later);
    printf("+100 days   : %s (difftime = %.0f s = %.0f days)\n",
           buf, difftime(t_later, now), difftime(t_later, now) / 86400);

    /* measure CPU time of some work */
    clock_t start = clock();
    volatile double x = 0;
    for (long i = 0; i < 20000000; i++) x += i * 0.5;
    clock_t end = clock();
    printf("loop took   : %.3f s CPU time\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
