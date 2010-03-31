/*
    Test LibLCDgr - Copyright (C) 2009 Ivan A-R <ivan@tuxotronic.org>

    This file is part of liblcdgr project

    LibLCDgr is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    LibLCDgr is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes LibLCDgr, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file main.c
 * @brief Test unit
 * @addtogroup Test
 * @{
 */

/* Includes ------------------------------------------------------------------*/

#include "config.h"
#include "lcd.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static char toHex(int v);

/* Private functions ---------------------------------------------------------*/

void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

extern void delayMs(int ms)
{
    int i;
    while(ms--)
    {
        for(i=0; i<9000; i++)
            asm volatile (" nop ");
    }
}


volatile int sysTick = 0;

void SysTick_Handler(void)
{
    sysTick++;
}

volatile int tim2Tick = 0;
volatile int haveTick = 0;


void TIM2_IRQHandler(void)
{
    static char led_state = 0;
    tim2Tick++;
    if(led_state)
        GPIOB->BSRR = GPIO_Pin_9;
    else
        GPIOB->BRR = GPIO_Pin_9;
    led_state = ~led_state;
    haveTick = 1;
    GPIOB->BSRR = GPIO_Pin_8;
    TIM2->SR = 0;
}

void initTim2(void)
{
    TIM2->CR1 = TIM_CR1_DIR;
    TIM2->CR2 = 0;
    TIM2->CNT = 0;
    TIM2->PSC = 10; // 10000;

    TIM2->ARR = 3600;
    TIM2->SR = 0;

    TIM2->DIER = TIM_DIER_UIE;
    // TODO !!!
    NVIC_SetPriority (TIM2_IRQn, (1<<__NVIC_PRIO_BITS)/2); // - 1);                               /* set Priority for Cortex-M0 System Interrupts */
    NVIC_EnableIRQ (TIM2_IRQn);
    TODO

    TIM2->EGR = TIM_EGR_UG;
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = TIM_CR1_CEN | TIM_CR1_DIR;

}




/**
  * @brief  Main program.
  * @param  None
  * @retval : None
  */
int main(void)
{
    /* Setup STM32 system (clock, PLL and Flash configuration) */
    SystemInit();

    SysTick_Config(7200000);

    RCC->APB2ENR |=  RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB;

    GPIOA->CRL = 0x88888888; // In_Pull
    GPIOA->CRH = 0x88888888; // In_Pull
    GPIOA->ODR = 0xFFFFFFFF;
    GPIOB->CRL = 0x38888888; // In_Pull
    GPIOB->CRH = 0x88888833; // In_Pull
    GPIOB->ODR = 0xFFFFFFFF;
    GPIOC->CRL = 0x88888888; // In_Pull
    GPIOC->CRH = 0x88888888; // In_Pull
    GPIOC->ODR = 0xFFFFFFFF;


    lcdInit();
    GPIOB->BSRR = GPIO_Pin_7; // LCD backlight on

    lcdSetBgColor(lcdGetColor(128, 0, 128));
    lcdClean();

    lcdSetFgColor(lcdGetColor(0, 255, 0));
    lcdBox(4, 4, 63+4, 63+4);
    lcdSetFgColor(lcdGetColor(255, 0, 0));
    lcdBox(32+4, 32+4, 95+4, 95+4);
    lcdSetFgColor(lcdGetColor(255, 255, 0));
    lcdBox(64+4, 64+4, 127+4, 127+4);

    lcdSetFgColor(0);
    lcdBox(20, 20, 131-20, 50);
    lcdSetFgColor(0xFFFF);
    lcdBox(22, 22, 131-22, 48);


    lcdSetBgColor(lcdGetColor(0xCC, 0xCC, 0xCC));
    lcdSetFgColor(lcdGetColor(0, 0, 0));
    lcdFillRect(20+4, 131-40, 131-20, 131-20, 1);

    //GPIOB->BSRR = GPIO_Pin_8;

    lcdSetFgColor(0x001F);
    lcdSetBgColor(0xFFFF);
    lcdCharXY(24+4, 131-40+4, 'H');
    lcdTextXY(24, 24, "Ready");

    lcdSetFgColor(lcdGetColor(0xFF, 0x99, 0x00));
    lcdBox(10, 10, 20, 20);

    //GPIOB->BSRR = GPIO_Pin_9;

    lcdSetFgColor(lcdGetColor(128, 0, 0));

    initTim2();
    asm(" CPSIE I ");

    int cnt = 0;
    char str[9];
    str[8] = 0;
    while (1)
    {
        /*
         *if(cnt != tim2Tick)
         *{
         */
            cnt = tim2Tick; // TIM2->CNT; // tim2Tick;
            str[0] = toHex((cnt>>28) & 0x0F);
            str[1] = toHex((cnt>>24) & 0x0F);
            str[2] = toHex((cnt>>20) & 0x0F);
            str[3] = toHex((cnt>>16) & 0x0F);
            str[4] = toHex((cnt>>12) & 0x0F);
            str[5] = toHex((cnt>>8) & 0x0F);
            str[6] = toHex((cnt>>4) & 0x0F);
            str[7] = toHex((cnt>>0) & 0x0F);
            lcdTextXY(24+16, 131-40+4, str);
            //cnt++;
        /*
         *}
         */
    }
}

static char toHex(int v)
{
    char r = v & 0x0F;
    if(r < 10)
        return (r + '0');
    else
        return (r + 'A' - 10);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
