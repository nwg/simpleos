#ifndef __TERMINAL_H__
#define __TERMINAL_H__

void term_init();
void term_write(const char *str);

void term_clear();

int kprintf(const char * restrict format, ...);

#endif
