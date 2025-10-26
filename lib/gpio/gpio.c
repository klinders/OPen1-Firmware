
#include "gpio.h"
#include "cmsis_os2.h"


led_t green_led = {
  .gpio = {
    .port=GPIOD,
    .pin=GPIO_PIN_12
  }
};

led_t orange_led = {
  .gpio={
    .port=GPIOD,
    .pin=GPIO_PIN_13
  }
};

led_t red_led = {
  .gpio = {
    .port=GPIOD,
    .pin=GPIO_PIN_14
  }
};

led_t blue_led = {
  .gpio = {
    .port=GPIOD,
    .pin=GPIO_PIN_15
  }
};

gpio_t i2s_enable = {
  .port=GPIOD,
  .pin=GPIO_PIN_4
};

/* Definitions for gpioTask */
osThreadId_t gpioTaskHandle;
const osThreadAttr_t gpioTask_attributes = {
  .name= "gpioTask",
  .stack_size= 128 * 4,
  .priority= (osPriority_t) osPriorityLow,
};

void GPIO_Init(void)
{


  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  led_init(&green_led);
  led_init(&red_led);
  led_init(&blue_led);
  led_init(&orange_led);
  gpio_init(&i2s_enable);

  // Start a task
  gpioTaskHandle = osThreadNew(StartGPIOTask, NULL, &gpioTask_attributes);
}

void StartGPIOTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    update_output(&green_led);
    update_output(&red_led);
    update_output(&blue_led);
    update_output(&orange_led);

    osDelay(LED_REFRESH_RATE);
  }
}

void gpio_init(gpio_t* g)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = g->pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(g->port, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(g->port, g->pin, GPIO_PIN_RESET);
}


void gpio_set(gpio_t* g)
{
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(g->port, g->pin, GPIO_PIN_SET);
}

void gpio_reset(gpio_t* g)
{
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(g->port, g->pin, GPIO_PIN_RESET);
}

void gpio_toggle(gpio_t* g)
{
  HAL_GPIO_TogglePin(g->port, g->pin);
}

void led_init(led_t* led)
{
  gpio_init(&led->gpio);
}

void turn_on(led_t* led)
{
  led->state = LED_ON;
  gpio_set(&led->gpio);
}

void turn_off(led_t* led)
{
  led->state = LED_OFF;
  gpio_reset(&led->gpio);
}

void blink(led_t* led)
{
  led->state = LED_BLINK;
}

void fast_blink(led_t* led)
{
  led->state = LED_FAST_BLINK;
}

void slow_blink(led_t* led)
{
  led->state = LED_SLOW_BLINK;
}

void update_output(led_t* led)
{
  if(led->counter > 0){
    led->counter--;
    return;
  }

  switch(led->state)
  {
    case LED_BLINK:
    gpio_toggle(&led->gpio);
    led->counter = BLINK_COUNT;
    break;

    case LED_FAST_BLINK:
    gpio_toggle(&led->gpio);
    led->counter = FAST_BLINK_COUNT;
    break;

    case LED_SLOW_BLINK:
    gpio_toggle(&led->gpio);
    led->counter = SLOW_BLINK_COUNT;
    break;

    default:
    break;
  }
}