#include "show.h"
#include "oled.h"

void show_task(void *pvParameters)
{
   u32 lastWakeTime = getSysTickCnt();
   while(1)
    {	

			vTaskDelayUntil(&lastWakeTime, F2T(RATE_50_HZ));

			// oled_show();   
				oled_timer();
    }
}  

// exercise b
void oled_show(void)
{  
		char message[] = "hello world\0";
		const u8* p = (const u8*) &message;
		OLED_ShowString(0, 0, p);
	 
		//call some function in oled to display something

		OLED_Refresh_Gram(); //refresh the OLED RAM
}

// exercise c
void oled_timer(void)
{  
		int time_interval = 950; // milliseconds
	  
		u8 tens_x = 0;
		u8 ones_x = 8;
	
		int tens = 0;
		char tens_char = '0' + tens;
	
		int ones = 0;
		char ones_char = '0' + ones;
	
		while(1)
    {
				OLED_ShowChar(tens_x, 0, tens_char, 12, 1);
        OLED_ShowChar(ones_x, 0, ones_char, 12, 1);

				++ones;
				if (ones > 9)
				{
						ones = 0;
						++tens;
					
						if (tens > 5)
						{
								tens = 0;
						}
				}
				
				tens_char = '0' + tens;
				ones_char = '0' + ones;
				
        delay_ms(time_interval);
				
				//call some function in oled to display something

				OLED_Refresh_Gram(); //refresh the OLED RAM
    }
}
