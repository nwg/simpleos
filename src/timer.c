#include "timer.h"
#include "intel_8254.h"

uint64_t g_timer_ticks = 0;
uint64_t g_timer_tps;
uint64_t g_timer_tps_divisor = 1;

void timer_tick() {
    g_timer_ticks += 1;
}