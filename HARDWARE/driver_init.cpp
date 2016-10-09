

#include "driver_init.h"


/*
*********************************************************************************************************
*                                               Driver_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : 
*********************************************************************************************************
*/

void  Driver_Init (void)
{ 
	uart_init(115200);		//初始化串口波特率为115200
	
	LED_Init();				//初始化LED
	fsmc.Init();
	
	//开启外部中断
//	EXTIX_Init();

}

///*
//*********************************************************************************************************
//*                                           BSP_LED_Init()
//*
//* Description : Initialize any or all the LEDs on the board.
//*
//* Argument(s) : led     The ID of the LED to control:
//*
//*                       0    inialize ALL  LEDs
//*                       1    inialize user LED1
//*                       2    inialize user LED2
//*                       3    inialize user LED3
//*                       4    inialize user LED4
//*
//* Return(s)   : none.
//*
//* Caller(s)   : Application.
//*
//* Note(s)     : none.
//*********************************************************************************************************
//*/
//static void  BSP_LED_Init()
//{
//    GPIO_InitTypeDef  gpio_init;


//    BSP_PeriphEn(BSP_PERIPH_ID_IOPCEN);                         /* Configure GPIOC for LED1 LED2 and LED3               */

//    gpio_init.GPIO_Pin   = BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3;
//    gpio_init.GPIO_Mode  = GPIO_Mode_OUT;
//    gpio_init.GPIO_OType = GPIO_OType_PP;
//    gpio_init.GPIO_PuPd  = GPIO_PuPd_UP;
//    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

//    GPIO_Init(GPIOC, &gpio_init);


//    BSP_PeriphEn(BSP_PERIPH_ID_IOPDEN);                         /* Configure GPIOD for LED4                             */

//    gpio_init.GPIO_Pin = BSP_GPIOD_LED4;

//    GPIO_Init(GPIOD, &gpio_init);
//}

///*
//*********************************************************************************************************
//*                                             BSP_LED_On()
//*
//* Description : Turn ON any or all the LEDs on the board.
//*
//* Argument(s) : led     The ID of the LED to control:
//*
//*                       0    turns ON ALL  LEDs
//*                       1    turns ON user LED1
//*                       2    turns ON user LED2
//*                       3    turns ON user LED3
//*                       4    turns ON user LED4
//*
//* Return(s)   : none.
//*
//* Caller(s)   : Application.
//*
//* Note(s)     : none.
//*********************************************************************************************************
//*/

//void  BSP_LED_On (CPU_INT08U  led)
//{
//    switch (led) {
//        case 0:
//             GPIO_SetBits(GPIOC, (BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3));

//             GPIO_SetBits(GPIOD, BSP_GPIOD_LED4);
//             break;

//        case 1:
//             GPIO_SetBits(GPIOC, BSP_GPIOC_LED1);
//             break;

//        case 2:
//             GPIO_SetBits(GPIOC, BSP_GPIOC_LED2);
//             break;

//        case 3:
//             GPIO_SetBits(GPIOC, BSP_GPIOC_LED3);
//             break;

//        case 4:
//             GPIO_SetBits(GPIOD, BSP_GPIOD_LED4);
//             break;

//        default:
//             break;
//    }
//}

///*
//*********************************************************************************************************
//*                                              BSP_LED_Off()
//*
//* Description : Turn OFF any or all the LEDs on the board.
//*
//* Argument(s) : led     The ID of the LED to control:
//*
//*                       0    turns OFF ALL the LEDs
//*                       1    turns OFF user LED1
//*                       2    turns OFF user LED2
//*                       3    turns OFF user LED3
//*                       4    turns OFF user LED4
//*
//* Return(s)   : none.
//*
//* Caller(s)   : Application.
//*
//* Note(s)     : none.
//*********************************************************************************************************
//*/

//void  BSP_LED_Off (CPU_INT08U led)
//{
//    switch (led) {
//        case 0:
//             GPIO_ResetBits(GPIOC, (BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3));

//             GPIO_ResetBits(GPIOD, BSP_GPIOD_LED4);
//             break;

//        case 1:
//             GPIO_ResetBits(GPIOC, BSP_GPIOC_LED1);
//             break;

//        case 2:
//             GPIO_ResetBits(GPIOC, BSP_GPIOC_LED2);
//             break;

//        case 3:
//             GPIO_ResetBits(GPIOC, BSP_GPIOC_LED3);
//             break;

//        case 4:
//             GPIO_ResetBits(GPIOD, BSP_GPIOD_LED4);
//             break;

//        default:
//             break;
//    }
//}


///*
//*********************************************************************************************************
//*                                            BSP_LED_Toggle()
//*
//* Description : TOGGLE any or all the LEDs on the board.
//*
//* Argument(s) : led     The ID of the LED to control:
//*
//*                       0    TOGGLE ALL the LEDs
//*                       1    TOGGLE user LED1
//*                       2    TOGGLE user LED2
//*                       3    TOGGLE user LED3
//*                       4    TOGGLE user LED4
//*
//* Return(s)   : none.
//*
//* Caller(s)   : Application.
//*
//* Note(s)     : none.
//*********************************************************************************************************
//*/

//void  BSP_LED_Toggle (CPU_INT08U  led)
//{
//    CPU_INT32U  pins;


//    switch (led) {
//        case 0:
//             pins  =  GPIO_ReadOutputData(GPIOC);
//             pins ^= (BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3);
//             GPIO_SetBits(  GPIOC,   pins  & (BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3));
//             GPIO_ResetBits(GPIOC, (~pins) & (BSP_GPIOC_LED1 | BSP_GPIOC_LED2 | BSP_GPIOC_LED3));

//             pins  =  GPIO_ReadOutputData(GPIOD);
//             pins ^= BSP_GPIOD_LED4;
//             GPIO_SetBits(  GPIOD,   pins  & BSP_GPIOD_LED4);
//             GPIO_ResetBits(GPIOD, (~pins) & BSP_GPIOD_LED4);
//             break;

//        case 1:
//             pins  = GPIO_ReadOutputData(GPIOC);
//             pins ^= BSP_GPIOC_LED1;
//             GPIO_SetBits(  GPIOC,   pins  & BSP_GPIOC_LED1);
//             GPIO_ResetBits(GPIOC, (~pins) & BSP_GPIOC_LED1);
//             break;

//        case 2:
//             pins  = GPIO_ReadOutputData(GPIOC);
//             pins ^= BSP_GPIOC_LED2;
//             GPIO_SetBits(  GPIOC,   pins  & BSP_GPIOC_LED2);
//             GPIO_ResetBits(GPIOC, (~pins) & BSP_GPIOC_LED2);
//             break;

//        case 3:
//             pins  =  GPIO_ReadOutputData(GPIOC);
//             pins ^= BSP_GPIOC_LED3;
//             GPIO_SetBits(  GPIOC,   pins  & BSP_GPIOC_LED3);
//             GPIO_ResetBits(GPIOC, (~pins) & BSP_GPIOC_LED3);
//             break;

//        case 4:
//             pins  =  GPIO_ReadOutputData(GPIOD);
//             pins ^= BSP_GPIOD_LED4;
//             GPIO_SetBits(  GPIOD,   pins  & BSP_GPIOD_LED4);
//             GPIO_ResetBits(GPIOD, (~pins) & BSP_GPIOD_LED4);
//             break;

//        default:
//             break;
//    }
//}






