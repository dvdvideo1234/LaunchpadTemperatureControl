#include "msp430G2231.h"
#include "mytypes.h"
#include "devapi.h"
#include "common.h"

#define PIN_FAN_PWM BIT6  // PWM output to the 4-pin FAN's PWN input  P1.6
#define PIN_FAN_ENB BIT7  // Start/Stop the fan via GPIO       output P1.7
#define PIN_ANL_TMP BIT5  // Where the temperature sensor is hooked   P1.5
#define PWM_PERIOD 512    // How much the PWM period will be
