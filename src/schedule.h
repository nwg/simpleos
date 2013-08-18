#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "process.h"
#include <stdbool.h>

#define K_STACK_SIZE 65536
#define U_STACK_SIZE 65536

void schedule_init();
void switch_to_process(process_t *process);
void schedule();
bool process_running();
void return_from_schedule(void *sp);
void add_process(process_t *process);
process_t *current_process();
void spawn(void *text, int argc, char **argv);
void remove_process(process_t *process);
#endif
