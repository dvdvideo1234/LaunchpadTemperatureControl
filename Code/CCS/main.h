#define ADC_RESOLUTION 0x3ff
#define PWM_RESOLUTION 0xffff   

void wdtStop(void)
{
  WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
}

void gpioReset(void)
{
  P1OUT = 0x00;
  P1DIR = 0x00;
  P1SEL = 0x00;
}

void gpioOutPin(u8 ucPin)
{
  P1DIR |= ucPin;
  P1OUT &= ~ucPin;
}

void gpioInPin(u8 ucPin, u8 ucIE)
{
  P1REN |= ucPin; //Enables a puller-Resistor on the button-pin
  P1SEL &= ~ucPin // Act as GPIO port
  P1OUT |= ucPin; //Writes a "1" to the portpin, tellling the resistor to pullup
  if(ucIE > 0)
  {
    //P1IES &= ~BUTTON; // Triggers when you RELEASE the button :: ...or pick the other
    P1IES |= ucPin; //Triggers when you PRESS the button :: Pick one...
  }
}

void gpioSet(u8 ucPin, u8 ucState)
{
	if(ucState)
  { // Set 1 for HIGH, 0 for LOW
    P1OUT |= ucPin;
  }
	else
  {
    P1OUT &= ~ucPin;
  }
}

void gpioGet(u8 ucPin)
{
  if((P1IN & (1 << ucPin)) == 0){ return 0xFF; }
	return 0x00;
}

void adcReset(void)
{
  ADC10CTL0 = 0x0000;
  ADC10CTL1 = 0x0000;
  ADC10AE0  = 0x0000;
}

void adcInitSingleOnce(u8 ucPin, u8 ucChan, u8 ucIE)
{
  adcReset();
  P1SEL     |=  ucPin;     // Special input
  P1DIR     &= ~ucPin;     // Direction input
  ADC10CTL0 |= SREF_0;     // VR+ = AVCC and VR- = AVSS  3.6-0 [V]
  ADC10CTL0 |= ADC10SHT0;  // Sample and hold mode
  ADC10CTL0 |= ADC10SHT_2; // Conversion time: 16 x ADC10CLKs    
  ADC10CTL0 |= ADC10ON;    // On/Enable 
  ADC10AE0  |= ucPin;      // Physical Pin select for analogue
  ADC10CTL1 |= ucChan;     // Select ADC Channel
  ADC10CTL1 |= SHS_0;      // Source from > Start convertion
  ADC10CTL1 |= ADC10DIV_0; // Clock divider _[ 0 ]
  ADC10CTL1 |= ADC10SSEL_2 // Clock comes from MCLK
  ADC10CTL1 |= CONSEQ_0    // Single channel single conversion
  if(ucIE)
  {
    ADC10CTL0 |= ADC10IFG | ADC10IE
  }
}

u8 adcIsBusy(void)
{
  if(ADC10CTL1 & ADC10BUSY)
  {
    return 0xff;
  }
  return 0x00;
}

u16 adcRead(void)
{
  ADC10CTL0 |= ENC;        // Enable conversion
  ADC10CTL0 |= ADC10SC;    // Start conversion
  while(adcIsBusy());
  return ADC10MEM;
}

u16 adcReadChannel(u16 ucChan)
{
	ADC10CTL0 &= ~ENC; 				         // Disable ADC 
	ADC10CTL0  = ADC10SHT_2 + ADC10ON; // Use 16 clocks and start
	ADC10CTL1  = ADC10SSEL_2;          // Clock from MCLK
  ADC10CTL1 |= ucChan;               // Select channel
	ADC10CTL0 |= ENC + ADC10SC; 			 // Enable and start conversion
	while(adcIsBusy());		 // Wait for conversion
	return ADC10MEM;
}

void timerReset(void)
{
  CCTL1 = 0x0000;
  TACTL = 0x0000;
}

void timerInitPWM(u8 ucPin)
{
  timerReset();
  P1DIR |= ucPin;             // Configure Pin
  P1SEL |= ucPin;             // Configure Pin Special
  TACTL |= MC_1;              // Counts up ( Up mode 0-CCR0 )
  TACTL |= TASSEL_2           // Clock SMCLK
  CCTL1 |= OUTMOD_7;          // CCR1 reset/set
}

void timerSetPeriodPWM(u16 uiPeriod)
{
  CCR0 = uiPeriod-1; // PWM Period
}

void timerSetDutyPWM(u16 uiDuty)
{ 
  if((uiDuty-1) <= CCR0)
  {
    CCR1 = uiDuty-1; // CCR1 PWM duty cycle
  }
}
