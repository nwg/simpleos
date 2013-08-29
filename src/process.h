#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "sizes.h"
#include "stack.h"
#include <unistd.h>
#include <stdbool.h>
#include "kernel.h"
#include "file.h"
#include "user.h"

#define K_STACK_SIZE 65536
#define U_STACK_SIZE 65536

#define PROCESS_MAX_FILES 16

typedef enum {
  PROCESS_RUNNABLE,
  PROCESS_SLEEPING,
  PROCESS_WAIT_READ,
  PROCESS_WAIT_WRITE,
} process_runstate_e;

typedef struct {
  uint64_t fileno;
  file_t *file;
} fileinfo_t;

typedef union {
  uint64_t sleep_until_tick;
  fileinfo_t fileinfo;
} runstate_u;

struct process_s;

typedef struct process_s {
  void *stack_k;
  void *stack_u;
  void *pages;
  system_state_t *state;
  system_state_t *kstate;
  void *saved_registers;
  void *text;
  file_t **files;
  process_runstate_e runstate;
  runstate_u runinfo;
  uint64_t num_pages;
  void *pt;
  int argc;
  char **argv;
  bool current;
  bool next_switch_is_kernel;
} process_t;

#define GET_USER_STACK_VMA(stack_u, address) ((uintptr_t)address - (uintptr_t)(stack_u) + USER_STACK_VMA)
#define GET_USER_STACK_PMA(stack_u, address) ((uintptr_t)address - USER_STACK_VMA + (uintptr_t)(stack_u))

process_t *process_alloc(void *text, int argc, char **argv);

void switch_to_process(process_t *process);
void process_stash_state(process_t *process, system_state_t *state);
void process_add_pages(process_t *process, uint64_t num);

void dump_process(process_t *p);
void process_description(char *buf, int n, process_t *p);
void process_sleep(process_t *process, useconds_t useconds);
void process_check_sleep(process_t *process);
void process_wake(process_t *process);
void switch_from_process(process_t *process);
ssize_t process_read_file(process_t *process, int filedes, char *buf, size_t len);
ssize_t process_write_file(process_t *this, int fileno, const char *buf, size_t len);
bool process_runnable(process_t *this);

#endif
