

#include "audio.h"
#include "gpio.h"
#include "dma.h"
#include <math.h>
#include "i2s.h"
#include "i2c.h"
#include "CS43L22.h"

/* USER CODE BEGIN 0 */
float mySinVal;
float sample_dt;
uint16_t sample_N;
uint16_t i_t;

uint32_t myDacVal;

int16_t dataI2S[100];
/* USER CODE END 0 */

/* Private variables ---------------------------------------------------------*/
#define PI 3.14159f

//Sample rate and Output freq
#define F_SAMPLE		96000.0f
#define F_OUT			2100.0f


void start_dma(void)
{
    sample_dt = F_OUT/F_SAMPLE;
	sample_N = F_SAMPLE/F_OUT;
    /* USER CODE BEGIN 2 */
	CS43_Init(hi2c1, MODE_I2S);
	CS43_SetVolume(20); //0 - 100,, 40
	CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
	CS43_Start();
	
	//Build Sine wave
	for(uint16_t i=0; i<sample_N; i++)
	{
		mySinVal = sinf(i*2*PI*sample_dt);
		dataI2S[i*2] = (mySinVal )*8000;    //Right data (0 2 4 6 8 10 12)
		dataI2S[i*2 + 1] =(mySinVal )*8000; //Left data  (1 3 5 7 9 11 13)
	}

	gpio_set(&i2s_enable);

	//HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t *)dataI2S, sample_N*2);
}

void stop_dma(void)
{
	// gpio_reset(&i2s_enable);
	//CS43_SetVolume(0); //0 - 100,, 40

}