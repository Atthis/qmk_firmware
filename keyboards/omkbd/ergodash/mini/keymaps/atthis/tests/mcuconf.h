#pragma once

#include_next <mcuconf.h>

#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE
// #undef RP_SIO_USE_UART1
// #define RP_SIO_USE_UART1 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE
