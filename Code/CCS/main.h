#include "msp430G2231.h"
#include "mytypes.h"
#include "devapi.h"
#include "common.h

// PWM output on P1.5 ( TA0.1 )
#define PIN_PWM_FAN BIT6
// Sensor input on P1.5 ( A5 )
#define PIN_AN_TEMP BIT5
// Coefficient monitor and control
#define PIN_BT_KOEF_U BIT3
#define PIN_BT_KOEF_D BIT4
#define PIN_KOEF_LED  BIT0
#define PWM_PERIOD 1000

