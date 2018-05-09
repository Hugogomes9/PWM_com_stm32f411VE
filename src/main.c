/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void TIMER_INIT(){
	TIM_TimeBaseInitTypeDef TIM_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_struct.TIM_Prescaler=0;
	TIM_struct.TIM_Period=9999;
	TIM_struct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_struct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_struct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&TIM_struct);
	TIM_Cmd(TIM4,ENABLE);
}
void TIM_PWM_INIT(){
TIM_OCInitTypeDef TIM_struct2;
TIM_struct2.TIM_OCMode=TIM_OCMode_PWM2;
TIM_struct2.TIM_OutputState=TIM_OutputState_Enable;
TIM_struct2.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_struct2.TIM_Pulse = 2499; /* 25% duty cycle */
    TIM_OC1Init(TIM4, &TIM_struct2);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_struct2.TIM_Pulse = 4999; /* 50% duty cycle */
    TIM_OC2Init(TIM4, &TIM_struct2);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_struct2.TIM_Pulse = 7499; /* 75% duty cycle */
    TIM_OC3Init(TIM4, &TIM_struct2);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_struct2.TIM_Pulse = 9999; /* 100% duty cycle */
    TIM_OC4Init(TIM4, &TIM_struct2);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
int main(void)
{
  TIM_PWM_INIT();
  TIMER_INIT();
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
 /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function,
       refer to system_stm32f4xx.c file */

  /* SysTick end of count event each 10ms */

  /* Add your application code here */
  /* Insert 50 ms delay */
   Delay(5);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD,&GPIO_InitStructure);


  /* Infinite loop */
int i;
  while (1)
  {
	  for(i=0;i<9999;i+=50){
		  TIM_SetCompare2(TIM4,i);
		  Delay(2);
	  }
	  for(i=9999;i>0;i-=50){
		  TIM_SetCompare2(TIM4,i);
		  Delay(2);
	  }
	  /*Delay(20);
	  GPIO_ToggleBits(GPIOD, GPIO_Pin_13);*/
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  {
    uwTimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
