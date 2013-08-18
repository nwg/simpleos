#include "kernel.h"
#include "schedule.h"
#include "memory.h"
#include "kmem.h"
#include "pages.h"
#include "asm.h"
#include "video.h"
#include "timer.h"

uintptr_t *kernel_pml4;
uintptr_t *kernel_pdpt;
uintptr_t *kernel_pdt;
uintptr_t *kernel_pt;
uint64_t kernel_ticks = 0;

/**
 * Configure first 2MB for initial kernel use
 */
void init_kernel_pages() {
	kernel_pml4 = kalloc_aligned(4096, 4096);
	kernel_pdpt = kalloc_aligned(4096, 4096);
	kernel_pdt = kalloc_aligned(4096, 4096);
	kernel_pt = kalloc_aligned(4096, 4096);

	for (int i = 0; i < 512; i++) {
		kernel_pml4[i] = (uintptr_t)kernel_pdpt | PAGE_PRESENT;
		kernel_pdpt[i] = (uintptr_t)kernel_pdt | PAGE_PRESENT;
		kernel_pdt[i] = (uintptr_t)kernel_pt | PAGE_PRESENT;
	}

	// Just an identity map of first 2MB of memory
	for (int i = 0; i < 512; i++) {
		kernel_pt[i] = i*4096 | PAGE_PRESENT | PAGE_WRITEABLE;
	}

    int voffset = (USER_VIDEO & PAGE_DIRENT_MASK) / PAGE_DIRENT_SIZE;
    kernel_pt[voffset] = 0xb8000 | PAGE_PRESENT | PAGE_WRITEABLE | PAGE_USER;
    kernel_pt[voffset + 1] = 0xb9000 | PAGE_PRESENT | PAGE_WRITEABLE | PAGE_USER;

	SET_CR3(kernel_pml4);
}

void spawn_test_programs() {
	static char *argv1[] = {
		"user1", "4", "11",
	};
	static int argc1 = sizeof(argv1) / sizeof(char*);

	spawn((void*)TEST_PROG_PMA, argc1, argv1);

	static char *argv2[] = {
	"user2", "1", "12",
	};
	static int argc2 = sizeof(argv2) / sizeof(char*);

	spawn((void*)TEST_PROG_PMA, argc2, argv2);

}

void kernel_init() {
	init_kernel_pages();
	schedule_init();
	init_timer();
}

#include <stdio.h>
void handle_timer_interrupt() {
	// printf("Timer");
	timer_tick();
	schedule();
}
