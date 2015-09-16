#include "main.h"

u8  ucStart = 0;
u16 uiAdcVL = 0;
u8  ucKoefU = 0;
u16 uiDuty  = 0;

void main(void)
{
  // Stop the bull-dog
  wdtStop();
  // Adjust CPU Clock CALBC1_16MHZ;
  setSystemCLK(CALBC1_12MHZ);
  // Configure the GPIO
  gpioOutPin(PIN_KOEF_LED);
  /*
  gpioInPin(PIN_BT_KOEF_U + PIN_BT_KOEF_D);
  */
  // Configure the ADC
  adcInitSingleOnce(PIN_AN_TEMP,INCH_5);
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
    if(uiAdcVL < 287)
    {
      gpioSet(PIN_KOEF_LED,1);
    }
    else
    {
      gpioSet(PIN_KOEF_LED,0);
    }
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

