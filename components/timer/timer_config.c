#include "timer_config.h"
#include "driver/gptimer.h"
#include "esp_timer.h"

static const char *TAG = "time";
static void periodic_timer_callback(void* arg);
extern volatile uint32_t time;
extern bool flagTime;
gptimer_handle_t gptimer = NULL;

void init_timer_bus(void)
{
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT, // Select the default clock source
        .direction = GPTIMER_COUNT_UP,      // Counting direction is up
        .resolution_hz = 1 * 1000 * 1000,   // Resolution is 1 MHz, i.e., 1 tick equals 1 microsecond
    };
    // Create a timer instance
    gptimer_new_timer(&timer_config, &gptimer);
    // Enable the timer
    gptimer_enable(gptimer);

}

void start_timer(void)
{
    gptimer_start(gptimer);
}

// ============================================================
void timerInit(void)
{
    const esp_timer_create_args_t periodic_timer_args =
        {
            .callback = &periodic_timer_callback,
            /* name is optional, but may help identify the timer when debugging */
            .name = "periodic"
        };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1000000));
}

static void periodic_timer_callback(void* arg)
{
    ++time;
    flagTime = true;
    if (time > 82800)
    {
        time = 0;
    }
    
}