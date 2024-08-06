/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include <cstdio>
#include <vector>
#include <iostream>
#include "common.h"
#include "open_table.h"
#include "util_static_allocator.h"
#include "stack.hpp"

#ifdef __cplusplus
extern "C" {
#endif
extern void initialise_monitor_handles(void);
#ifdef __cplusplus
}
#endif
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
UART_HandleTypeDef UartHandle;
#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define TABLESIZE 182

#ifndef NL
#define NL printf("\n")
#endif

void table_test1();
void table_test_unique();
void test_placement_stl();
void test_stack();
int passed=0;
int failed=0;
int tcs=0;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	Heap_Init();
	initialise_monitor_handles();
	table_test1();
	table_test_unique();
	test_placement_stl();
	test_stack();


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART1 configured as follow:
        - Word Length = 8 Bits
        - Stop Bit = One Stop bit
        - Parity = ODD parity
        - BaudRate = 9600 baud
        - Hardware flow control disabled (RTS and CTS signals) */
    UartHandle.Instance          = USART2;

    UartHandle.Init.BaudRate     = 9600;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_ODD;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    MX_USART2_UART_Init();


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  printf("hello arm");
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_ODD;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
/*-----------------------------------------------------------------------------
Test functions and data
-----------------------------------------------------------------------------*/
void test_placement_stl()
{

	std::vector<int, util::static_allocator<int>> vec;

	    // Perform operations on the vector
	    vec.push_back(1);
	    vec.push_back(2);
	    vec.push_back(3);

	    // Print the elements using the [] operator
	    for (size_t i = 0; i < vec.size(); ++i) {
	        std::cout << vec[i] << " ";
	    }
	    std::cout << std::endl;
}
void table_test1()
{

	open_table table;
	table_init(&table, TABLESIZE, hash1, hash2);


	double a[] = {
	0.534027, 0.194275, 0.682942, 0.989345, 0.221968, 0.432571, 0.753486, 0.084738, 0.593845, 0.728294,
	0.382974, 0.892475, 0.483927, 0.128374, 0.392845, 0.756349, 0.574829, 0.283746, 0.987435, 0.274859,
	0.638472, 0.293847, 0.748293, 0.923847, 0.347592, 0.947293, 0.738492, 0.293846, 0.598372, 0.847362,
	0.837462, 0.273846, 0.837492, 0.948372, 0.384756, 0.273849, 0.758293, 0.374859, 0.238749, 0.984725,
	0.382749, 0.283746, 0.948273, 0.283745, 0.847362, 0.938472, 0.283746, 0.473829, 0.928374, 0.827365,
	0.392847, 0.758394, 0.283746, 0.938472, 0.273846, 0.847362, 0.283746, 0.483927, 0.984726, 0.283746,
	0.847362, 0.293846, 0.837492, 0.384759, 0.273846, 0.837492, 0.473829, 0.938472, 0.283745, 0.847362,
	0.392847, 0.938472, 0.283746, 0.847362, 0.283746, 0.938472, 0.283746, 0.837492, 0.384759, 0.283746,
	0.847362, 0.283746, 0.938472, 0.283746, 0.847362, 0.283746, 0.938472, 0.283746, 0.847362, 0.283746,
	0.837492, 0.938472, 0.283746, 0.847362, 0.938472, 0.283746, 0.847362
	};

	for (size_t i = 0; i < _countof(a); i++) {
		table_insert(&table, a[i]);
	}

	analyze_clusters(&table);
	table_destroy(&table);

}

void table_test_unique()
{
	open_table table;
	table_init(&table, TABLESIZE, hash1, hash2);

	double a[] = {
	0.135235, 0.269456, 0.371928, 0.485627, 0.591734, 0.623895, 0.737465, 0.849273, 0.963728, 0.174592,
	0.285746, 0.397582, 0.514728, 0.628935, 0.739486, 0.857391, 0.973658, 0.185937, 0.296573, 0.408765,
	0.519473, 0.629847, 0.742865, 0.859374, 0.973485, 0.198473, 0.309846, 0.421759, 0.532847, 0.645927,
	0.758293, 0.869534, 0.982759, 0.210945, 0.324897, 0.435986, 0.546897, 0.658374, 0.769348, 0.873495,
	0.986537, 0.223748, 0.337592, 0.450726, 0.564937, 0.672348, 0.785639, 0.896453, 0.998345, 0.236789,
	0.349485, 0.463927, 0.579843, 0.685372, 0.795736, 0.907482, 0.122847, 0.132857, 0.142756, 0.152857,
	0.162362, 0.172857, 0.182756, 0.192839, 0.202857, 0.212726, 0.222626, 0.232756, 0.242726, 0.252829,
	0.262726, 0.272626, 0.282726, 0.292839, 0.302756, 0.312726, 0.322726, 0.332839, 0.342726, 0.352726,
	0.362839, 0.372726, 0.382726, 0.392839, 0.402726, 0.412726, 0.422839, 0.432726, 0.442726, 0.452839,
	0.462726, 0.472726, 0.482839, 0.492726, 0.502726, 0.512839, 0.522726
	};



	for (size_t i = 0; i < _countof(a); i++) {
		table_insert(&table, a[i]);
	}

	analyze_clusters(&table);
	table_destroy(&table);

}

void test_stack() {
    // Test 1: Push and Pop Sequence
	TC_BEGIN("Test 1: Push and Pop Sequence");
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int exp[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    stack<int> s;
    for (auto& i : a) {
        s.push(i);  // Use variable `i`, no change needed here
    }
    for (auto& i : exp) {
    	auto tmp = s.pop();
    	VERIFY(i == tmp);
    }


    // Test 2: Pop from an empty stack
    TC_BEGIN("Test 2: Pop from an empty stack");
    stack<int> empty_stack;
    VERIFY(empty_stack.pop() == 0);  // Expect default value (0 for int)
    VERIFY(empty_stack.empty());


    // Test 3: Push to full capacity and pop
    TC_BEGIN("Test 3: Push to full capacity and pop")
    stack<int, 5> small_stack;
    for (int i = 0; i < 5; ++i) {
        small_stack.push(i);
    }
    VERIFY(!small_stack.empty());

    // Attempt to push another element (should not be added)
    TC_BEGIN("Attempt to push another element (should not be added)");
    int value_to_push = 5;
    small_stack.push(value_to_push);  // Should print "full"
    for (int i = 4; i >= 0; --i) {
    	auto tmp = small_stack.pop();
        VERIFY(tmp == i);
    }


    // Test 4: Mixed operations
    TC_BEGIN("Test 4: Mixed operations");
    stack<int> mixed_stack;
    int v1 = 10, v2 = 20, v3 = 30, v4 = 40;
    mixed_stack.push(v1);
    mixed_stack.push(v2);
    auto tmp = mixed_stack.pop();
    VERIFY(tmp == v2);
    mixed_stack.push(v3);
    mixed_stack.push(v4);
    tmp = mixed_stack.pop();
    VERIFY(tmp == v4);
    tmp = mixed_stack.pop();
    VERIFY(tmp == v3);
    tmp = mixed_stack.pop();
    VERIFY(tmp == v1);
    VERIFY(mixed_stack.empty());


    // Test 5: Check for stack underflow handling
    TC_BEGIN("Test 5: Check for stack underflow handling");
    stack<int> underflow_stack;
    VERIFY(underflow_stack.pop() == 0);  // Expect default value
    REPORT("test_stack")
}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
