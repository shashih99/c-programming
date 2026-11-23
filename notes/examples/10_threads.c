/* 10_threads.c - POSIX threads: create/join, passing args, race condition, mutex
 * Build:  gcc -Wall -Wextra -std=c11 -pthread 10_threads.c -o threads */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 4
#define ITERS    1000000

typedef struct {               /* pass several values to a thread via a struct */
    int id;
    long from, to;
    long result;               /* thread writes its result here */
} Task;

void *partial_sum(void *arg)
{
    Task *t = arg;
    long s = 0;
    for (long i = t->from; i <= t->to; i++) s += i;
    t->result = s;
    return NULL;
}

long counter_unsafe = 0;
long counter_safe = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *inc_unsafe(void *arg)
{
    (void)arg;
    for (int i = 0; i < ITERS; i++)
        counter_unsafe++;      /* read-modify-write: NOT atomic -> data race */
    return NULL;
}

void *inc_safe(void *arg)
{
    (void)arg;
    for (int i = 0; i < ITERS; i++) {
        pthread_mutex_lock(&lock);
        counter_safe++;        /* critical section: one thread at a time */
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void)
{
    pthread_t th[NTHREADS];

    /* 1. split work: sum of 1..1,000,000 across 4 threads */
    Task tasks[NTHREADS];
    long chunk = 1000000 / NTHREADS;
    for (int i = 0; i < NTHREADS; i++) {
        tasks[i] = (Task){ .id = i, .from = i * chunk + 1, .to = (i + 1) * chunk };
        if (pthread_create(&th[i], NULL, partial_sum, &tasks[i]) != 0) {
            fprintf(stderr, "pthread_create failed\n");
            return 1;
        }
    }
    long total = 0;
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(th[i], NULL);                 /* wait for the thread to finish */
        printf("thread %d summed %ld..%ld = %ld\n", tasks[i].id, tasks[i].from, tasks[i].to, tasks[i].result);
        total += tasks[i].result;
    }
    printf("total = %ld (expected %ld)\n", total, 1000000L * 1000001L / 2);

    /* 2. race condition vs mutex */
    for (int i = 0; i < NTHREADS; i++) pthread_create(&th[i], NULL, inc_unsafe, NULL);
    for (int i = 0; i < NTHREADS; i++) pthread_join(th[i], NULL);
    for (int i = 0; i < NTHREADS; i++) pthread_create(&th[i], NULL, inc_safe, NULL);
    for (int i = 0; i < NTHREADS; i++) pthread_join(th[i], NULL);

    printf("expected count  = %d\n", NTHREADS * ITERS);
    printf("without mutex   = %ld  <- lost updates (varies run to run)\n", counter_unsafe);
    printf("with mutex      = %ld\n", counter_safe);
    pthread_mutex_destroy(&lock);
    return 0;
}
