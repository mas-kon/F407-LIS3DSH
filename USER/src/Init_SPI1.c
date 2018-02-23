#include "Init_SPI1.h"

/* ========================================================================== */
void InitSPI1(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;					// Enable Clock GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;					// Enable Clock GPIOE
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;						// Enable Clock SPI1

	// GPIOE3 - SPI1 CS
	/* Configure GPIOE as output, meduim speed, no pull-up, pull-down */
	SPI1_CS_PORT->MODER 	&= 	~GPIO_MODER_MODER3_1;
	SPI1_CS_PORT->MODER 	|= 	 GPIO_MODER_MODER3_0;
	SPI1_CS_PORT->OTYPER	&= 	~GPIO_OTYPER_OT_3;
	SPI1_CS_PORT->PUPDR 	&= 	~GPIO_PUPDR_PUPDR3;
	SPI1_CS_PORT->OSPEEDR |= 	 GPIO_OSPEEDER_OSPEEDR3_0;
	SPI1_CS_PORT->OSPEEDR &= 	~GPIO_OSPEEDER_OSPEEDR3_1;

	// GPIOA5 - SPI1 SCK
	SPI1_SCK_PORT->MODER 		&= ~GPIO_MODER_MODER5_0;			// Alternate func
	SPI1_SCK_PORT->MODER 		|= 	GPIO_MODER_MODER5_1;
	SPI1_SCK_PORT->OSPEEDR 	|= 	GPIO_OSPEEDER_OSPEEDR5_0;	// Very high speed
	SPI1_SCK_PORT->OSPEEDR 	|= 	GPIO_OSPEEDER_OSPEEDR5_1;
	SPI1_SCK_PORT->PUPDR 		&= ~GPIO_PUPDR_PUPDR5;				// No PP
	SPI1_SCK_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL5_0;				// Alternate func AF5 SPI1
	SPI1_SCK_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL5_1;				// Alternate func AF5 SPI1
	SPI1_SCK_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL5_2;				// Alternate func AF5 SPI1
	SPI1_SCK_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL5_3;				// Alternate func AF5 SPI1
	
	// GPIOA6 - SPI1 MISO
	SPI1_MISO_PORT->MODER 	&= ~GPIO_MODER_MODER6_0;			// Alternate func
	SPI1_MISO_PORT->MODER 	|= 	GPIO_MODER_MODER6_1;
	SPI1_MISO_PORT->OSPEEDR |= 	GPIO_OSPEEDER_OSPEEDR6_0;	// Very high speed
	SPI1_MISO_PORT->OSPEEDR |= 	GPIO_OSPEEDER_OSPEEDR6_1;
	SPI1_MISO_PORT->PUPDR 	&= ~GPIO_PUPDR_PUPDR6;				// No PP
	SPI1_MISO_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL6_0;				// Alternate func AF5 SPI1
	SPI1_MISO_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL6_1;				// Alternate func AF5 SPI1
	SPI1_MISO_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL6_2;				// Alternate func AF5 SPI1
	SPI1_MISO_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL6_3;				// Alternate func AF5 SPI1

	// GPIOA7 - SPI1 MOSI
	SPI1_MOSI_PORT->MODER 	&= ~GPIO_MODER_MODER7_0;			// Alternate func
	SPI1_MOSI_PORT->MODER 	|= 	GPIO_MODER_MODER7_1;
	SPI1_MOSI_PORT->OSPEEDR |= 	GPIO_OSPEEDER_OSPEEDR7_0;	// Very high speed
	SPI1_MOSI_PORT->OSPEEDR |= 	GPIO_OSPEEDER_OSPEEDR7_1;
	SPI1_MOSI_PORT->PUPDR 	&= ~GPIO_PUPDR_PUPDR7;				// No PP
	SPI1_MOSI_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL7_0;				// Alternate func AF5 SPI1
	SPI1_MOSI_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL7_1;				// Alternate func AF5 SPI1
	SPI1_MOSI_PORT->AFR[0] 	|=  GPIO_AFRL_AFSEL7_2;				// Alternate func AF5 SPI1
	SPI1_MOSI_PORT->AFR[0] 	&= ~GPIO_AFRL_AFSEL7_3;				// Alternate func AF5 SPI1

	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;				//Reset module SPI1
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
	SPI1->CR1 = 0x0;
	
	SPI1->CR1 |= SPI_CR1_MSTR;
	
	SPI1->CR1 |= SPI_CR1_SSM;										// Soft slave select
	SPI1->CR1 |= SPI_CR1_SSI;
	
	SPI1->CR1 |= SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;

	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;						// MSB transmitted first
	SPI1->CR1 &= ~SPI_CR1_RXONLY;							// Full duplex
	SPI1->CR1 &= ~SPI_CR1_DFF;								// 8bit frame format

	SPI1->CR1 |=  SPI_CR1_BR_0;								// Baud rate control
	SPI1->CR1 &= ~SPI_CR1_BR_1;
	SPI1->CR1 &= ~SPI_CR1_BR_2;
	
	SPI1->CR1 |= SPI_CR1_SPE;
}

/* ========================================================================== */
void SPI1_ON(GPIO_TypeDef* _SPIgpio, uint16_t _SPIpin)
{				
	GPIOPinReset(_SPIgpio, _SPIpin);
}

/* ========================================================================== */
void SPI1_OFF(GPIO_TypeDef* _SPIgpio, uint16_t _SPIpin)
{
	GPIOPinSet(_SPIgpio, _SPIpin);
}

/* ========================================================================== */
uint8_t SPI1SendData(uint8_t data)
{	
		while (!(SPI1->SR & SPI_SR_TXE)){};
			SPI1->DR = data;	
		while (!(SPI1->SR & SPI_SR_RXNE)){};
			data = SPI1->DR;
		return data;
}

/* ========================================================================== */
void SPI1_WriteRegister(uint8_t registerAddress, uint8_t registerData)
{
	SPI1_ON(SPI1_CS_PORT, SPI1_CS_PIN);	
	SPI1SendData( registerAddress );
	SPI1SendData( registerData );
	SPI1_OFF(SPI1_CS_PORT, SPI1_CS_PIN);
}

/* ========================================================================== */
uint8_t SPI1_ReadRegister(uint8_t registerAddress)
{
	SPI1_ON(SPI1_CS_PORT, SPI1_CS_PIN);	
	uint8_t registerData; 
	registerAddress |= (0x01<<7);
	SPI1SendData( registerAddress );
	registerData = SPI1SendData( 0x0F );
	SPI1_OFF(SPI1_CS_PORT, SPI1_CS_PIN);
	return registerData;	
}
