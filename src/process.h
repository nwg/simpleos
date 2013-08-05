#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "types.h"
#include "sizes.h"
#include "stack.h"

#define K_STACK_SIZE 65536
#define U_STACK_SIZE 65536

typedef struct process_s {
  void *stack_k;
  void *stack_u;
  void *pages;
  void *saved_sp;
  void *saved_registers;
  void *text;
  u64_t num_pages;
  void *pt;
  int argc;
  char **argv;
} process_t;

#define USER_STACK_VMA 0x200000
#define USER_STACK_START ((uintptr_t)STACK(USER_STACK_VMA, U_STACK_SIZE))
#define USER_TEXT_VMA 0x210000
#define USER_TEXT_SIZE (16*K)
#define USER_HEAP 0x300000

#define GET_USER_STACK_VMA(stack_u, address) ((uintptr_t)address - (uintptr_t)(stack_u) + USER_STACK_VMA)

process_t *process_alloc(void *text, int argc, char **argv);

void __attribute__ ((noreturn)) switch_to_process(process_t *process);
void return_from_process(process_t *process, void *sp);
void process_add_pages(process_t *process, u64_t num);

#endif
