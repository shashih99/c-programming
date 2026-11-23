/* 10_signals.c - catching signals with sigaction; safe handlers; raise, alarm, kill (POSIX)
 * Interactive: run it and press Ctrl+C within 3 seconds. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t got_sigint = 0;     /* the ONLY kind of variable a handler should set */
static volatile sig_atomic_t got_alarm = 0;
static volatile sig_atomic_t got_usr1 = 0;

static void handler(int sig)
{
    /* async-signal-safe only: no printf, malloc, etc. Just set a flag (or call write()). */
    if (sig == SIGINT)  got_sigint = 1;
    if (sig == SIGALRM) got_alarm = 1;
    if (sig == SIGUSR1) got_usr1 = 1;
}

int main(void)
{
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    raise(SIGUSR1);                              /* send a signal to ourselves */
    if (got_usr1) printf("caught SIGUSR1 (via raise)\n");

    got_sigint = 0;
    kill(getpid(), SIGINT);                      /* same thing via kill(pid, sig) */
    if (got_sigint) printf("caught SIGINT (via kill) - program keeps running\n");
    got_sigint = 0;

    printf("press Ctrl+C within 3 seconds (or wait for SIGALRM)...\n");
    fflush(stdout);
    alarm(3);                                    /* kernel sends SIGALRM in 3 s */
    while (!got_sigint && !got_alarm)
        pause();                                 /* sleep until any signal arrives */

    if (got_sigint) printf("caught SIGINT from keyboard, cleaning up\n");
    else            printf("caught SIGALRM: timeout\n");

    signal(SIGINT, SIG_DFL);                     /* restore default action (terminate) */
    printf("exiting normally\n");
    return 0;
}
