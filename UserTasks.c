/*****************************************************************************
 * Module 	  : FreeRTOS User Story2 Tasks implementation
 *
 * File name  : UserStory1.c
 *
 * Created on : Oct 5, 2019
 *
 * Author     : Ahmed Eldakhly
 ******************************************************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "UserTasks.h"

/*******************************************************************************
 *                           static Global Variables                           *
 *******************************************************************************/
static uint8 PressedKey = 0;
static uint8 Init_Done = 0;
static TaskHandle_t  AllHardwareInit_Flag = NULL;
static uint8 DisplayFlag = 0;

/*******************************************************************************
 *                           Global Variables                    		       *
 *******************************************************************************/
TaskHandle_t  InitTask_Flag = NULL;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	init_Task
 *
 * Description: 	Create all tasks in the system
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void init_Task(void * a_Task_ptr)
{

	xTaskCreate(All_Hardware_Init_Task  , "InitTasks" , configMINIMAL_STACK_SIZE ,
			NULL , (4 | portPRIVILEGE_BIT) , &AllHardwareInit_Flag);
	xTaskCreate(KeyPad_Task  , "KeyPad_Task" , configMINIMAL_STACK_SIZE ,
			NULL , (2 | portPRIVILEGE_BIT) , NULL);
	xTaskCreate(LCD_Task  , "LCD_Task" , configMINIMAL_STACK_SIZE ,
			NULL , (1 | portPRIVILEGE_BIT) , NULL);
	vTaskSuspend( InitTask_Flag);
}

/*******************************************************************************
 * Function Name:	All_Hardware_Init_Task
 *
 * Description: 	Initialize LCD & KeyPad
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void All_Hardware_Init_Task(void * a_Task_ptr)
{

	while(1)
	{
		KeyPad_Init();
		LCD_init();
		Init_Done++;
		vTaskSuspend( AllHardwareInit_Flag);


	}
}

/*******************************************************************************
 * Function Name:	KeyPad_Task
 *
 * Description: 	KeyPad Task
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void KeyPad_Task(void * a_Task_ptr)
{
	/*de_bouncing Flag to make sure key is pressed*/
	uint8 Debouncing = 0;

	/*comparing value to check if key is pressed*/
	uint8 OldPressedValue = 0;

	while(1)
	{
		if(Init_Done == 0)
		{

			/*Do Nothing*/
		}
		else
		{
			if(Debouncing == 0 && KeyPad_getPressedKey()!=10)
			{
				OldPressedValue =  KeyPad_getPressedKey();
				Debouncing++;
				vTaskDelay(10);
			}
			else if(Debouncing == 1)
			{
				if(OldPressedValue == KeyPad_getPressedKey())
				{
					PressedKey = OldPressedValue;
					DisplayFlag = 1;
				}
				else
				{
					/*Do Nothing*/
				}
				Debouncing++;
				vTaskDelay(100);
			}
			else
			{
				Debouncing = 0;
				vTaskDelay(100);

			}
		}
	}

}

/*******************************************************************************
 * Function Name:	LCD_Task
 *
 * Description: 	LCD Task
 *
 * Inputs:			pointer to void
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_Task(void * a_Task_ptr)
{
	/*counter to count entered numbers*/
	uint8 PasswordCounter=0;

	/*Password*/
	uint8 Password[]= "153426";

	uint8 Correct[]= "Correct Password";

	/*to check on correct answer*/
	uint8 CorrectFlag = 0;

	while(1)
	{
		if(DisplayFlag == 1 && PressedKey < 7 && PasswordCounter < 6)
		{
			LCD_displayCharacter(PressedKey + 48);
			DisplayFlag = 0;
			if((Password[PasswordCounter] == (PressedKey+48)) && CorrectFlag == 0)
			{
				/*Do Nothing*/
			}
			else
			{
				CorrectFlag = 1;
			}
			PasswordCounter++;
		}
		else if(PressedKey == 7)
		{
			LCD_clearScreen();
			PasswordCounter = 0;
			CorrectFlag = 0;
		}
		else if(PressedKey == 9 && PasswordCounter == 6)
		{
			if(CorrectFlag == 0)
			{
				LCD_clearScreen();
				LCD_displayString(Correct);
				PasswordCounter = 0;
				vTaskDelay(2000);
				LCD_clearScreen();
			}
			else
			{
				PasswordCounter = 0;
				LCD_clearScreen();
				CorrectFlag = 0;
			}
		}

		vTaskDelay(150);
	}


}
