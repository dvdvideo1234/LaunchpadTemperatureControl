#include "msp430G2231.h"
#include "mytypes.h"
#include "main.h"

// PWM output on P1.5 ( TA0.1 )
#define PIN_PWM_FAN BIT6
// Sensor input on P1.5 ( A5 )
#define PIN_AN_TEMP BIT5
// Coefficient monitor and control
#define PIN_BT_KOEF_U BIT3
#define PIN_BT_KOEF_D BIT4
#define PIN_KOEF_LED  BIT1

u8  ucStart = 0;
u16 uiAdcVL = 0;

void main(void)
{
  wdtStop();
  // Configure the GPIO
  gpioReset();
  gpioOutPin(PIN_KOEF_LED);
  gpioInPin(PIN_BT_KOEF_U | PIN_BT_KOEF_D,0);
  // Configure the ADC
  adcReset();
  adcInitSingleOnce(PIN_AN_TEMP,INCH_5,0)
  // Configure the PWM
  timerReset();
  timerInitPWM(PIN_PWM_FAN)
  timerSetPeriodPWM(1000)
  timerSetDutyPWM(250)
  
  ucStart = 0xff;
  
  for(;;)
  {
    uiAdcVL = adcGetValue();
  }
}

/* Timer ISR
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A_0(void)
{
  
}
*/
/*
// Port 1 ISR
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  
}
*/
/*
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{

}
*/
