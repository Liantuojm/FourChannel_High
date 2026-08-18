#include "relay.h"
#include "mb.h"


void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 开启按键GPIO口的时钟 */
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY9_GPIO_CLK,ENABLE);
	
  /* 选择按键的引脚 */
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN; 
  
  /* 设置引脚为输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  
  /* 设置引脚不上拉也不下拉 */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  /* 使用上面的结构体初始化按键 */
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);  
  
  /* 选择按键的引脚 */
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN; 
  
  /* 使用上面的结构体初始化按键 */
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);  
	
	/* 选择按键的引脚 */
	GPIO_InitStructure.GPIO_Pin = KEY9_PIN; 
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 使用上面的结构体初始化按键 */
	GPIO_Init(KEY9_GPIO_PORT, &GPIO_InitStructure); 	
}

void Relay_Config(void)
{
	/* 定义一个GPIO_InitTypeDef类型的结构体 */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 开启LED相关的GPIO外设时钟 */
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOI
												| RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOH
												| RCC_AHB1Periph_GPIOG, ENABLE); 

	/* 选择要控制的GPIO引脚 */															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	

	/* 设置引脚模式为输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	
	/* 设置引脚的输出类型为推挽输出 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	
	/* 设置引脚为上拉模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	/* 设置引脚速率为2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 

	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_11 | GPIO_Pin_2;
	GPIO_Init(GPIOI, &GPIO_InitStructure);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 选择要控制的GPIO引脚 */															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	

	/* 设置引脚模式为输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
		
	/*设置引脚为上拉模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

	/* 设置引脚速率为2MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	
	/* 调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO */
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	relay1_OFF;
	relay2_OFF;
	relay3_OFF;
	relay4_OFF;
	relay5_OFF;
	relay6_OFF;
	relay7_OFF;
	relay8_OFF;
	relay9_OFF;
	relay10_OFF;
	relay11_OFF;
	relay12_OFF;
	relay13_OFF;
	relay14_OFF;
	relay15_OFF;
	relay16_OFF;
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/* 检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON)  
	{	 
		/*等待按键释放 */
		//while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
	{
		return KEY_OFF;
	}
}


