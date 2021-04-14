#include "led.h"

int Led_Count;//LED blink Delay 

//LED initialization
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = LED_PIN;				//LED Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//Push pull output
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(LED_PORT, &GPIO_InitStructure);			//Initialize LED GPIO
	GPIO_SetBits(LED_PORT,LED_PIN);
}

void led_task(void *pvParameters)
{
		// exercise A part 1
    int delay_amount = 5000; // in milliseconds
    
    while(1)
    {
        LED=~LED;        //0 on, 1 off   
        // delay_ms(500);	
        delay_ms(delay_amount);
        // vTaskDelay(Led_Count); //Delay 
    }
}  

