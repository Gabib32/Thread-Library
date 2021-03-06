#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define STACK_SIZE 1024*1024

typedef enum {
	RUNNING,
	READY, 
	BLOCKED, 
	DONE
} state_t;

struct mutex {
	int held;
        struct queue waiting_threads;
} typedef mutex;

struct condition {
	struct queue waiting_threads;
} typedef condition;

struct thread {
        unsigned char* stack_pointer;
        void (*initial_function)(void*);
        void* initial_argument;
	state_t state;
	mutex mutex;
	condition condition;
} typedef thread;

extern thread *current_thread;

void thread_start(thread *old, thread *new);
void thread_switch(thread * old, thread *new);

void mutex_init(mutex *);
void mutex_lock(mutex *);
void mutex_unlock(mutex *);

void condition_init(condition *c);
void condition_wait(condition *c, mutex *m);
void condition_signal(condition *c);
void condition_broadcast(condition *c);

void thread_join(thread*);

void scheduler_begin();
thread * thread_fork(void(*target)(void*), void *arg);
void yield();
void scheduler_end();

