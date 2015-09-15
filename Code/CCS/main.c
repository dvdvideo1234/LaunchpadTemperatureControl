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
#define PIN_KOEF_LED  BIT0
#define PWM_PERIOD 1000

u8  ucStart = 0;
u16 uiAdcVL = 0;
u8  ucKoefU = 0;
u16 uiDuty  = 0;


void main(void)
{
  gpioReset();
  adcReset();
  timerReset();
  wdtStop();
  // Configure the GPIO
  gpioOutPin(PIN_KOEF_LED);
  gpioInPin(PIN_BT_KOEF_U + PIN_BT_KOEF_D);
  // Configure the ADC
  adcInitSingleOnce(PIN_AN_TEMP,INCH_5,0);
  // Configure the PWM
  /*
  timerInitPWM(PIN_PWM_FAN);
  timerSetPeriodPWM(PWM_PERIOD);
  timerSetDutyPWM(uiDuty);
  */
  ucStart = 0xff;
  
  for(;;)
  {
    uiAdcVL = adcRead();
    timerSetDutyPWM(uiAdcVL);
    if(gpioGet(PIN_BT_KOEF_U))
    {
      gpioSet(PIN_KOEF_LED,1);
    }
    else
    {
      gpioSet(PIN_KOEF_LED,0);
    }
    // if(uiDuty >= PWM_PERIOD){ uiDuty = 0; }
  }
}

#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A_0(void)
{
  
}

#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A_1(void)
{
  
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{

}

