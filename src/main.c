
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void clock(void);
void lat(void);
void oe(void);

uint8_t test_0[16][12]={
		  {0,0,0,0,0,1,1,0,0,0,0,0},
		  {0,0,0,1,1,1,1,1,1,0,0,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,0,0,1,1,1,1,0},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {0,1,1,1,1,0,0,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,0,0,1,1,1,1,1,1,0,0,0},
		  {0,0,0,0,0,1,1,0,0,0,0,0}
};

uint8_t test_1[16][12]={
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,1,1,1,1,0,0,0,0},
		  {0,0,0,1,1,1,1,1,0,0,0,0},
		  {0,0,1,1,1,1,1,1,0,0,0,0},
		  {0,1,1,1,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
};

uint8_t test_2[16][12]={
		  {0,0,0,0,0,1,1,1,1,0,0,0},
		  {0,0,0,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,0,0,0,0,1,1,1,0},
		  {1,1,1,0,0,0,0,0,1,1,1,0},
		  {1,1,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,1,1,1,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,1,1,1,0,0,0,0,0},
		  {0,0,0,1,1,1,0,0,0,0,0,0},
		  {0,0,1,1,1,0,0,0,0,0,0,0},
		  {0,1,1,1,0,0,0,0,0,0,0,0},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
};

uint8_t test_3[16][12]={
		  {0,0,1,1,1,1,1,1,1,0,0,0},
		  {0,1,1,1,1,1,1,1,1,1,0,0},
		  {1,1,1,1,1,1,1,1,1,1,1,0},
		  {1,1,1,0,0,0,0,1,1,1,1,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,1,1,1,1,0,0,0},
		  {0,0,0,0,0,1,1,1,1,0,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {1,1,1,0,0,0,0,1,1,1,1,0},
		  {1,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,0,0,0},
};

uint8_t test_4[16][12]={
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,1,1,1,1,0,0},
		  {0,0,0,0,0,1,1,1,1,1,0,0},
		  {0,0,0,0,1,1,1,1,1,1,0,0},
		  {0,0,0,1,1,1,0,1,1,1,0,0},
		  {0,0,1,1,1,0,0,1,1,1,0,0},
		  {0,1,1,1,0,0,0,1,1,1,0,0},
		  {1,1,1,0,0,0,0,1,1,1,0,0},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
};

uint8_t test_5[16][12]={
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,0,0,0,0,0,0,0},
		  {0,0,1,1,1,0,0,0,0,0,0,0},
		  {0,0,1,1,1,1,1,1,0,0,0,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,0,0,1,1,1},
		  {0,0,0,0,0,0,0,0,0,1,1,1},
		  {0,0,0,0,0,0,0,0,0,1,1,1},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,0,0,0},
};

uint8_t test_6[16][12]={
		  {0,0,0,0,1,1,1,1,1,1,1,1},
		  {0,0,1,1,1,1,1,1,1,1,1,1},
		  {0,1,1,1,1,1,1,1,1,1,1,1},
		  {0,1,1,1,0,0,0,0,0,0,0,0},
		  {1,1,1,0,0,0,0,0,0,0,0,0},
		  {1,1,1,0,0,1,1,1,1,0,0,0},
		  {1,1,1,1,1,1,1,1,1,1,0,0},
		  {1,1,1,1,1,1,1,1,1,1,1,0},
		  {1,1,1,1,0,0,0,0,1,1,1,0},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,1,0,0,0,0,1,1,1,0},
		  {1,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,0,0,0},
};

uint8_t test_7[16][12]={
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,0,1,1,1,0,0},
		  {0,0,0,0,0,0,1,1,1,0,0,0},
		  {0,0,0,0,0,0,1,1,1,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,0,1,1,1,0,0,0,0},
		  {0,0,0,0,1,1,1,0,0,0,0,0},
		  {0,0,0,0,1,1,1,0,0,0,0,0},
		  {0,0,0,1,1,1,0,0,0,0,0,0},
		  {0,0,1,1,1,0,0,0,0,0,0,0},
		  {0,0,1,1,1,0,0,0,0,0,0,0},
};

uint8_t test_8[16][12]={
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {0,1,1,1,0,0,0,0,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
		  {0,1,1,1,0,0,0,0,1,1,1,0},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,0,0,0,0,0,0,1,1,1},
		  {1,1,1,1,0,0,0,0,1,1,1,1},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,0,1,1,1,1,1,1,1,1,0,0},
};

uint8_t test_9[16][12]={
		  {0,0,0,0,1,1,1,1,1,1,0,0},
		  {0,0,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,1},
		  {0,1,1,1,1,0,0,0,1,1,1,1},
		  {0,1,1,1,0,0,0,0,0,1,1,1},
		  {0,1,1,1,0,0,0,0,0,1,1,1},
		  {0,1,1,1,1,0,0,0,1,1,1,1},
		  {0,1,1,1,1,1,1,1,1,1,1,1},
		  {0,0,1,1,1,1,1,1,1,1,1,1},
		  {0,0,0,1,1,1,1,1,0,1,1,1},
		  {0,0,0,0,0,0,0,0,0,1,1,1},
		  {0,0,0,0,0,0,0,0,0,1,1,1},
		  {0,0,0,0,0,0,0,0,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,1,0},
		  {0,1,1,1,1,1,1,1,1,1,0,0},
		  {0,1,1,1,1,1,1,1,0,0,0,0},
};

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int capture = 0;
  char buf[25];

//  int Y = 10;
  int X = 0;
  int PANEL_X_MAX=128;



  while (1)
  {
	  capture = TIM1->CNT;
	  X = round(capture/100);
//	  sprintf(buf,"count: [%ld]\n", capture);
//	  HAL_UART_Transmit_DMA(&huart3,buf,sizeof(buf)-1);



	  uint8_t pixel[32][128];
	  for (int j = 0; j < 32; j++)
		  {
		  	  for (int i = 0; i < PANEL_X_MAX; i++)
		 		  {
		  		  	  pixel[j][i]=0;
		 		  }
		  }


//	  for (int j = 0; j < 16; j++)
//		  {
//		  	  for (int i = 0; i < 12; i++)
//		 		  {
//		  		  	  pixel[j+8][X + i]=test_9[j][i];
//		 		  }
//		  }

	  uint8_t pixel_2[16][26];

	  for (int j = 0; j < 16; j++)
		  {
		  	  for (int i = 0; i < 26; i++)
		 		  {
		  		pixel_2[j][i]=0;
		 		  }
		  }

	  uint8_t pixel_1[16][12];
	  int numbers[2];
	  int test_data = 59;
	  int tens = test_data/10;
	  int ones = test_data%10;
	  numbers[0]=tens;
	  numbers[1]=ones;

	  for (int pix = 0; pix < 2; pix++){
		  for (int j = 0; j < 16; j++)
			  {
				  for (int i = 0; i < 12; i++)
					  {
					  	  switch(numbers[pix]){
					  	  case 0:
//					  		pixel_1 = test_0;
					  		memcpy(pixel_1, test_0, sizeof(pixel_1));
					  		break;
					  	  case 1:
					  		memcpy(pixel_1, test_1, sizeof(pixel_1));
					  		break;
					  	  case 2:
					  		memcpy(pixel_1, test_2, sizeof(pixel_1));
					  		break;
					  	  case 3:
					  		memcpy(pixel_1, test_3, sizeof(pixel_1));
					  		break;
					  	  case 4:
					  		memcpy(pixel_1, test_4, sizeof(pixel_1));
					  		break;
					  	  case 5:
					  		memcpy(pixel_1, test_5, sizeof(pixel_1));
					  		break;
					  	  case 6:
					  		memcpy(pixel_1, test_6, sizeof(pixel_1));
					  		break;
					  	  case 7:
					  		memcpy(pixel_1, test_7, sizeof(pixel_1));
					  		break;
					  	  case 8:
					  		memcpy(pixel_1, test_8, sizeof(pixel_1));
					  		break;
					  	  case 9:
					  		memcpy(pixel_1, test_9, sizeof(pixel_1));
					  		break;
					  	  }
//						  pixel[j+8][X + i]=test_9[j][i];
					  	pixel_2[j][pix*12 + pix*2 + i]=pixel_1[j][i];
					  }
			  }
	  }

	  for (int j = 0; j < 16; j++)
		  {
			  for (int i = 0; i < 26; i++)
				  {
					  pixel[j+8][X + i]=pixel_2[j][i];
				  }
		  }

	  int Y = 0;
	  for( int j = 0; j<16;j++){
//		  HAL_Delay(1);
//		  for(int d=0;d<0x500;d++);
//		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

		  Y= j;

		  sprintf(buf,"count: [%ld]\n", Y);
		  HAL_UART_Transmit_DMA(&huart3,buf,sizeof(buf)-1);

		  set_row(Y);
//		  Y++;
		  int x = 0;
		  for (int i = 0; i < PANEL_X_MAX; i++)
		  {
			  //top
			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,pixel[Y][i]);
			  //bottom
//			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,pixel[Y+16][i]);
			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,pixel[Y+16][i]);
			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,pixel[Y+16][i]);

			  clock();
		  } // for X
		  lat();
		  oe();
//		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	  } // for Y


	} //while

  } //main

void clock(){
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

void lat(){
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
}
void oe(){
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	  for(int d=0;d<0x700;d++);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
}

void set_row(int row){
	  if (row & 0x01) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
	  else HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);

	  if (row & 0x02) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
	  else HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);

	  if (row & 0x04) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
	  else HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);

	  if (row & 0x08) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
	  else HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_Encoder_InitTypeDef sConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 12800;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 57600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 
                           PB7 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
