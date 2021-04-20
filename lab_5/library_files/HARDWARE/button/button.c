#include "button.h"
#include "LED.h"
#include "playsong.h"
#include "show.h"

// code based on LED.c
// Practice A

//Buzzer initialization
void Button_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); //Enable APB Clock
	
	GPIO_InitStructure.GPIO_Pin = BUTTON_PIN;				//Buzzer Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// input - internal pull up
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50M
	GPIO_Init(BUTTON_PORT, &GPIO_InitStructure);			//Initialize Buzzer GPIO
	GPIO_SetBits(BUTTON_PORT,BUTTON_PIN);
}

// reference: https://www.handsonembedded.com/stm32f103-spl-tutorial-3/
void button_task(void *pvParameters)
{
	u8* song = (uint8_t*)
	"e2,d2,e2,d2,e2,B2,d2,c2,A2_C2,E2,A2,B2_E2,G2,B2,c4_E2,e2,d2,e2,d2,e2,B2,d2,c2,A2_C2,E2,A2,B2_E2,c2,B2,A4";
	
	/*
	char pressedMessage[] = 		"button pressed \0";
	char notPressedMessage[] = 	"button released\0";
	
	const u8* p1 = (const u8*) &pressedMessage;
	const u8* p2 = (const u8*) &notPressedMessage;
	*/
	
	int period = 2000;
	
	while(1)
	{
		if(!(GPIO_ReadInputData(BUTTON_PORT) & BUTTON_PIN))
		{
			//OLED_ShowString(0, 0, p1);
			playSong(song);
			
			period = (period == 500) ? 2000 : 500;
			changePeriod(period);
		}
		else
		{
			//OLED_ShowString(0, 0, p2);	
		}
		
		//OLED_Refresh_Gram(); //refresh the OLED RAM
	}
}  
