/*****************************************************************************
 * Module 	  : FreeRTOS User Story2 Tasks Prototypes
 *
 * File name  : UserStory1.h
 *
 * Created on : Oct 5, 2019
 *
 * Author     : Ahmed Eldakhly
 ******************************************************************************/

#ifndef USERTASKS_H_
#define USERTASKS_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "std_types.h"
#include "Macro.h"
#include "DIO.h"
#include "keypad.h"
#include "lcd.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
extern TaskHandle_t  InitTask_Flag;

/*******************************************************************************
 *                      Functions Prototypes        	                       *
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
void init_Task(void * a_Task_ptr);

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
void All_Hardware_Init_Task(void * a_Task_ptr);

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
void KeyPad_Task(void * a_Task_ptr);

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
void LCD_Task(void * a_Task_ptr);

#endif /* USERTASKS_H_ */
