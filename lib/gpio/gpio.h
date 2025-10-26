#pragma once

#include "stm32f4xx_hal.h"

// -- Defines -- //
#define LED_REFRESH_RATE    200 // ms
#define BLINK_COUNT         3
#define FAST_BLINK_COUNT    1
#define SLOW_BLINK_COUNT    12

// -- Type definitions -- //

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK,
    LED_FAST_BLINK,
    LED_SLOW_BLINK
} led_state_t;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} gpio_t;

typedef struct {
    gpio_t gpio;
    led_state_t state;
    uint16_t counter;
} led_t;


// -- End type definitions -- //

// -- Variables -- //

extern led_t green_led;
extern led_t red_led;
extern led_t blue_led;
extern led_t orange_led;
extern gpio_t i2s_enable;

// -- End variables -- //

// -- Functions -- //

void GPIO_Init(void);
void StartGPIOTask(void*);

void gpio_init(gpio_t*);
void gpio_set(gpio_t*);
void gpio_reset(gpio_t*);
void gpio_toggle(gpio_t*);

void turn_on(led_t*);
void turn_off(led_t*);
void blink(led_t*);
void fast_blink(led_t*);
void slow_blink(led_t*);
void update_output(led_t*);
void led_init(led_t*);

// -- End functions -- //
