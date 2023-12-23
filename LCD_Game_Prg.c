
#include "StdTypes.h"
#include "BUTTON_Int.h"
#include "LCD_Int.h"
#include "LCD_Game_Int.h"
#define F_CPU		8000000UL
#include <util/delay.h>

static u8 man_custom[8]= {0x04,0x04,0x1F,0x04,0x04,0x0A,0x11,0x00} ;
static u8 arrow[8]=	{0x08,0x04,0x02,0x1F,0x02,0x04,0x08,0x00} ;	
static u8 dead_man[8] = {0x15,0x0E,0x1F,0x04,0x04,0x0A,0x11,0x00}; 
static u8 init_flag = 0 ;
static u8 arr_pos = 2 ;

void LCD_Game_Init (void)
{
	LCD_Write_String_Cursor(1,3,(u8*)"<<WELCOME>>");
	LCD_Write_String_Cursor(2,3,(u8*)"Hunting Game");
	_delay_ms(3000);
	LCD_Clear_Screen();
	LCD_Custom_Char(0,man_custom);
	LCD_Custom_Char(1,arrow);
	LCD_Custom_Char(2,dead_man);
}

void LCD_Game_Runnable (void)
{
	if (0==init_flag)
	{
		LCD_Clear_Screen();
		arr_pos = 2 ;
		LCD_Set_Cursor(1,1);
		LCD_Write_Character(0);
		LCD_Set_Cursor(1,16);
		LCD_Write_Character(0);
		LCD_Set_Cursor(1,arr_pos);
		LCD_Write_Character(1);
		init_flag = 1 ;
	}
	if (BUTTON_Get_status(0)==BUTTON_PRESSED)
	{
		_delay_ms(10);
		LCD_Clear_Cursor(1,arr_pos,1);
		arr_pos += 1 ;
		if (16==arr_pos)
		{
			LCD_Clear_Cursor(1,16,1);
			LCD_Set_Cursor(1,arr_pos);
			LCD_Write_Character(2);
			LCD_Write_String_Cursor(2,1,(u8*)"<Target Killed>");
			_delay_ms(3000);
			init_flag = 0 ;
		}
		else
		{
			LCD_Set_Cursor(1,arr_pos);
			LCD_Write_Character(1);
		}
		
		while (BUTTON_Get_status(0)==BUTTON_PRESSED); // Busy Wait
		_delay_ms(10);
	}
	if (BUTTON_Get_status(1)==BUTTON_PRESSED)
	{
		init_flag = 0 ;
		_delay_ms(10);
		while (BUTTON_Get_status(1)==BUTTON_PRESSED);
		_delay_ms(10);
	}
}

