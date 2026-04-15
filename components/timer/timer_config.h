#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "timer_config.h"
#include "driver/gptimer.h"
#include "esp_log.h"

void init_timer_bus(void);
void timer_init_device(void);
void start_timer(void);
void timerInit(void);
// int64_t esp_timer_impl_get_time(void);
// int64_t esp_timer_get_time(void) __attribute__((alias("esp_timer_impl_get_time")));


#ifdef __cplusplus
}
#endif