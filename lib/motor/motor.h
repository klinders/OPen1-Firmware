
#include "stm32f4xx_hal.h"

typedef enum {
    MOTOR_OFF,
    MOTOR_ON
} motor_state_t;

typedef struct {
    GPIO_TypeDef* dir_port;
    uint16_t dir_pin;
    motor_state_t state;
    uint32_t counter;
    uint32_t step;

} stepper_t;


void init_motor(stepper_t*);
void start_motor(stepper_t*, uint8_t, uint32_t);
void stop_motor(stepper_t*);

extern stepper_t stepper1;