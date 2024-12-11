/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D4

// #undef SERIAL_USART_DRIVER
// #define SERIAL_USART_DRIVER SIOD1

// Cirque pointing device config
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN 2
#define I2C1_SCL_PIN 3
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll. #define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8

// #define POINTING_DEVICE_ROTATION_270
// #define CIRQUE_PINNACLE_TAP_ENABLE
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// #define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

// #define SERIAL_USART_FULL_DUPLEX
// #define SERIAL_PIO_USE_PIO0
// #define SERIAL_USART_RX_PIN 5
