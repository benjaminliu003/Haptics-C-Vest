// Support routines for ECE 198 (University of Waterloo)

// Written by Bernie Roehl, July 2021

#include <stdbool.h>  // for bool datatype

#include "ece198.h"

///////////////////////
// Initializing Pins //
///////////////////////

// Initialize a pin (or pins) to a particular mode, with optional pull-up or pull-down resistors
// and possible alternate function
// (we use this so students don't need to know about structs)

void InitializePin(GPIO_TypeDef *port, uint16_t pins, uint32_t mode, uint32_t pullups, uint8_t alternate)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pins;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pullups;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

/////////////////
// Serial Port //
/////////////////

UART_HandleTypeDef UART_Handle;  // the serial port we're using

// initialize the serial port at a particular baud rate (PlatformIO serial monitor defaults to 9600)

HAL_StatusTypeDef SerialSetup(uint32_t baudrate)
{
    __USART2_CLK_ENABLE();        // enable clock to USART2
    __HAL_RCC_GPIOA_CLK_ENABLE(); // serial port is on GPIOA

    GPIO_InitTypeDef GPIO_InitStruct;

    // pin 2 is serial RX
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // pin 3 is serial TX (most settings same as for RX)
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // configure the serial port
    UART_Handle.Instance = USART2;
    UART_Handle.Init.BaudRate = baudrate;
    UART_Handle.Init.WordLength = UART_WORDLENGTH_8B;
    UART_Handle.Init.StopBits = UART_STOPBITS_1;
    UART_Handle.Init.Parity = UART_PARITY_NONE;
    UART_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART_Handle.Init.Mode = UART_MODE_TX_RX;

    return HAL_UART_Init(&UART_Handle);
}

// wait for a character to arrive from the serial port, then return it

char SerialGetc()
{
    while ((UART_Handle.Instance->SR & USART_SR_RXNE) == 0)
        ;                             // wait for the receiver buffer to be Not Empty
    return UART_Handle.Instance->DR;  // return the incoming character
}

// send a single character out the serial port

void SerialPutc(char c)
{
    while ((UART_Handle.Instance->SR & USART_SR_TXE) == 0)
        ;                          // wait for transmitter buffer to be empty
    UART_Handle.Instance->DR = c;  // send the character
}

// write a string of characters to the serial port

void SerialPuts(char *ptr)
{
    while (*ptr)
        SerialPutc(*ptr++);
}

// get a string of characters (up to maxlen) from the serial port into a buffer,
// collecting them until the user presses the enter key;
// also echoes the typed characters back to the user, and handles backspacing

void SerialGets(char *buff, int maxlen)
{
    int i = 0;
    while (1)
    {
        char c = SerialGetc();
        if (c == '\r') // user pressed Enter key
        {
            buff[i] = '\0';
            SerialPuts("\r\n"); // echo return and newline
            return;
        }
        else if (c == '\b') // user pressed Backspace key
        {
            if (i > 0)
            {
                --i;
                SerialPuts("\b \b"); // overwrite previous character with space
            }
        }
        else if (i < maxlen - 1) // user pressed a regular key
        {
            buff[i++] = c;  // store it in the buffer
            SerialPutc(c);  // echo it
        }
    }
}

////////////////////////////
// Pulse Width Modulation //
////////////////////////////

// set up a specified timer with the given period (whichTimer might be TIM2, for example)

void InitializePWMTimer(TIM_HandleTypeDef *timer, TIM_TypeDef *whichTimer, uint16_t period, uint16_t prescale )
{
    timer->Instance = whichTimer;
    timer->Init.CounterMode = TIM_COUNTERMODE_UP;
    timer->Init.Prescaler = prescale;
    timer->Init.Period = period;
    timer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer->Init.RepetitionCounter = 0;
    HAL_TIM_PWM_Init(timer);
}

// set up a particular channel (e.g. TIM_CHANNEL_1) on the given timer instance

void InitializePWMChannel(TIM_HandleTypeDef *timer, uint32_t channel)
{
    TIM_OC_InitTypeDef outputChannelInit;
    outputChannelInit.OCMode = TIM_OCMODE_PWM1;
    outputChannelInit.OCPolarity = TIM_OCPOLARITY_HIGH;
    outputChannelInit.OCFastMode = TIM_OCFAST_ENABLE;
    outputChannelInit.Pulse = timer->Init.Period;
    HAL_TIM_PWM_ConfigChannel(timer, &outputChannelInit, channel);
    HAL_TIM_PWM_Start(timer, channel);
}

// set the number of ticks in a cycle (i.e. <= the timer's period) for which the output should be high

void SetPWMDutyCycle(TIM_HandleTypeDef *timer, uint32_t channel, uint32_t value)
{
    switch (channel)
    {
    case TIM_CHANNEL_1:
        timer->Instance->CCR1 = value;
        break;
    case TIM_CHANNEL_2:
        timer->Instance->CCR2 = value;
        break;
    case TIM_CHANNEL_3:
        timer->Instance->CCR3 = value;
        break;
    case TIM_CHANNEL_4:
        timer->Instance->CCR4 = value;
        break;
    }
}

/////////
// ADC //
/////////

// Written by Rodolfo Pellizzoni, September 2021

void InitializeADC(ADC_HandleTypeDef* adc, ADC_TypeDef* whichAdc)  // whichADC might be ADC1, for example
{
    adc->Instance = whichAdc;
    adc->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    adc->Init.Resolution = ADC_RESOLUTION_12B;
    adc->Init.ScanConvMode = DISABLE;
    adc->Init.ContinuousConvMode = DISABLE;
    adc->Init.DiscontinuousConvMode = DISABLE;
    adc->Init.NbrOfDiscConversion = 1;
    adc->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc->Init.NbrOfConversion = 1;
    adc->Init.DMAContinuousRequests = DISABLE;
    adc->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    HAL_ADC_Init(adc);
}

// read from the specified ADC channel

uint16_t ReadADC(ADC_HandleTypeDef* adc, uint32_t channel)  // channel might be ADC_CHANNEL_1 for example
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(adc, &sConfig);
    HAL_ADC_Start(adc);
    HAL_ADC_PollForConversion(adc, HAL_MAX_DELAY);
    uint16_t res = HAL_ADC_GetValue(adc);
    HAL_ADC_Stop(adc);
    return res;
}
