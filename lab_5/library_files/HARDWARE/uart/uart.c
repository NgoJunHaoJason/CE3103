#include "uart.h"
#include "show.h"

// Practice C
TimerHandle_t uartTimer;

void uart_init(u32 baudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
	//USART_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //C10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//USART_RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//UsartNVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//USART
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	
	// Practice C
	uartTimer = xTimerCreate(
		"SendUART1Sec", 			// name
		pdMS_TO_TICKS(1000),	// period
		pdTRUE,								// auto reload
		(void*) 0,						// timer ID
		uart_task							// callback
	);
	xTimerStart(uartTimer, pdMS_TO_TICKS(0));
}

// Practice C
void uart_task(void *pvParameters)
{
	u8 message = 'a';
	usart3_send(message);
}

// STM32 to computer
void usart3_send(u8 data)
{
	
	USART3->DR = data;
	
	while((USART3->SR & 0x40) == 0);
}

const u8* p;

// computer to STM32
int USART3_IRQHandler(void)
{
	static u8 Count=0,i;
	u8 Usart_Receive;
	static u8 rxbuf[10];
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		// USART_Receive is the received data
		Usart_Receive = USART_ReceiveData(USART3);
		
		p = (const u8*) Usart_Receive;
		OLED_ShowString(0, 0, p);
		OLED_Refresh_Gram(); //refresh the OLED RAM
	}
	
	return 0;
}
