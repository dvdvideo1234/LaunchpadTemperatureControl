#define ADC_RESOLUTION 0x3ff
#define PWM_RESOLUTION 0xffff   
#define POWER_VCC 353
// How many cycles to convert the value ( 16 )
#define ADC_CLK_SAMPLE ADC10SHT_2

void setSystemCLK(u16 uiClk)
{
  BCSCTL1 = uiClk;
  DCOCTL  = uiClk;
}

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
  P1SEL &= ~ucPin; // Not special
  P1DIR |=  ucPin; // Configure is an output
  P1OUT &= ~ucPin;
}

void gpioInPin(u8 ucPin)
{
  P1SEL &= ~ucPin;  // Not special
  P1DIR &= ~ucPin;  // Configure is an input
  P1OUT |= ucPin;   // pull-up resistor
  P1REN |= ucPin;   // resistor enabled
  P1IES |= ucPin;   // interrupt on low-to-high transition
  P1IE  |= ucPin;   // interrupt enable
}

void gpioSet(u8 ucPin, u8 ucState)
{
  // Set 1 for HIGH, 0 for LOW
  if(ucState){ P1OUT |= ucPin;  }
  else       { P1OUT &= ~ucPin; }
}

u8 gpioGet(u8 ucPin)
{
  if((P1IN & ucPin) != 0){ return 0xff; }
  return 0x00;
}

void adcReset(void)
{
  ADC10CTL0 = 0x0000;
  ADC10CTL1 = 0x0000;
  ADC10AE0  = 0x0000;
}

void adcInitSingleOnce(u8 ucPin, u16 uiChan)
{
  // Port P1 ADC Analogue Pin Functions
  ADC10AE0  |= ucPin;           // Physical Pin select for analogue
  ADC10CTL0 |= SREF_0;          // VR+ = AVCC [3.6V] and VR- = AVSS [0V]
  ADC10CTL0 |= ADC10SHT0;       // Sample and hold mode
  ADC10CTL0 |= ADC_CLK_SAMPLE;  // Conversion time: 16 x ADC10CLKs
  ADC10CTL0 |= ADC10IFG;        // Enable Interrupt flag 
  ADC10CTL0 |= ADC10IE;         // Interrupt Enable
  ADC10CTL0 |= ADC10ON;         // On/Enable
  ADC10CTL1 |= uiChan;          // Select ADC Channel
  ADC10CTL1 |= SHS_0;           // Source from > Start conversion
  ADC10CTL1 |= ADC10DIV_0;      // Clock divider _[ 0 ]
  ADC10CTL1 |= ADC10SSEL_2;     // Clock comes from MCLK
  ADC10CTL1 |= CONSEQ_0;        // Single channel single conversion
}

u8 adcIsBusy(void)
{
  if(ADC10CTL1 & ADC10BUSY){ return 0xff; } return 0x00;
}

u16 adcRead(void)
{
  ADC10CTL0 |= ENC;        // Enable conversion
  ADC10CTL0 |= ADC10SC;    // Start conversion
  while(adcIsBusy());
  return ADC10MEM;
}

u16 adcReadChannel(u16 uiChan)
{
  ADC10CTL0 &= ~ENC;               // Disable ADC
  ADC10CTL0 |=  ADC_CLK_SAMPLE     // Use ADC_CLK_SAMPLE clocks
  ADC10CTL0 |=  ADC10ON;           // Start the device
  ADC10CTL1  =  ADC10SSEL_2;       // Clock from MCLK
  ADC10CTL1 |=  uiChan;            // Select channel
  ADC10CTL0 |=  ENC;               // Enable conversion
  ADC10CTL0 |=  ADC10SC;           // Start conversion
  while(adcIsBusy());              // Wait for conversion
  return ADC10MEM;
}

void timerReset(void)
{
  CCTL1 = 0x0000;
  TACTL = 0x0000;
}

void timerInitPWM(u8 ucPin)
{
  // Port P1 Timer Pin Functions
  P1DIR |= ucPin;             // Configure Pin output
  P1SEL |= ucPin;             // Configure Pin Special
  TACTL |= MC_1;              // Counts up ( Up mode 0-CCR0 )
  TACTL |= TASSEL_2;          // Clock SMCLK
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

