#include "main.h"

#define kP 30
#define ERR_OFF 0
#define ERR_CDN 2000

s16 iAdc = 0;
s16 iDty = 0;
s16 iErr = 0;
s16 iRef = 68;
u16 uTim = 0;

void main(void)
{
  // Stop the bull-dog
  wdtStop();
  // Configure the GPIO
  gpioOutPin(PIN_FAN_ENB + LED_ERR);
  // Configure the ADC
  adcInitSingleOnce(PIN_ANL_TMP,INCH_5);
  // Configure the PWM
  timerInitPWM(PIN_FAN_PWM);
  timerSetPeriodPWM(PWM_PERIOD);
  timerSetDutyPWM(0);

  gpioSet(PIN_FAN_ENB,1);

  for(;;)
  {
    iAdc = (s16)adcReadN(15);
    iErr = iAdc - iRef;
    iDty = kP * iErr;
    // Power On-Off the fan to save power
    if(uTim)
    {
      gpioSet(PIN_FAN_ENB,0);
      timerSetDutyPWM(0);
      uTim--;
    }else{
      gpioSet(PIN_FAN_ENB,1);
      if(iErr < ERR_OFF)
      {
        gpioSet(PIN_FAN_ENB,0);
        timerSetDutyPWM(0);
        uTim = ERR_CDN;
      }
    }
    // Indicate the error
    if(iErr < ERR_OFF)
    {
      gpioSet(LED_ERR,1);
    }
    else
    {
      gpioSet(LED_ERR,0);
    }
    // Saturate the duty cycle
    if(iDty <= 0)
    {
      iDty = 0;
    }
    else if(iDty > (PWM_PERIOD-1))
    {
      iDty = (PWM_PERIOD-1);
    }
    timerSetDutyPWM(iDty);
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

