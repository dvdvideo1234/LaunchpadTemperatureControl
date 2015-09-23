#include "main.h"

#define kP 18

u8  ucStart = 0;
s16 uiAdcVL = 0;
s16 iDuty   = 0;
s16 iZero   = 0;
s16 iErr    = 0;
s16 vP      = 0;
s16 iRef    = 300;


void main(void)
{
  // Stop the bull-dog
  wdtStop();
  // Configure the GPIO
  gpioOutPin(PIN_FAN_ENB);
  // Configure the ADC
  adcInitSingleOnce(PIN_ANL_TMP,INCH_5);
  iZero = adcReadN(100)-20;
  // Configure the PWM
  timerInitPWM(PIN_FAN_PWM);
  timerSetPeriodPWM(PWM_PERIOD);
  timerSetDutyPWM(iDuty);

  ucStart = 0xff;
  
  for(;;)
  {
    iErr = (adcReadN(25)-iZero) - iRef;
    vP   = kP * iErr;
    uiDuty  = uiAdcVL * KP;
    timerSetDutyPWM(uiDuty);
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

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{

}

