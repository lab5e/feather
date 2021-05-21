/*
    Copyright [2021] [Lab5e AS]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.#include <zephyr.h>
*/   

#pragma once

#include <stdint.h>

#define COZIR_I2C_ADDRESS 0x41

#define COZIR_CO2_LEVEL_REGISTER            0x02   
#define COZIR_SENSOR_CONTROL_SETTINGS       0x05  
#define COZIR_AUTO_ZERO_TARGET              0x0C
#define COZIR_TARGET_VALUE_CO2_FRESH_AIR    0x12
#define COZIR_KNOWN_CO2                     0x14
#define COZIR_AUTO_ZERO_CYCLES              0x1A
#define COZIR_SERIAL_NUMBER_REGISTER        0x26
#define COZIR_NPULSE                        0x2A
#define COZIR_AUTO_ZERO_CONTROL             0x4E
#define COZIR_ALTITUDE_PRESSURE             0x76

int init_CozIR();
int read_CozIR_CO2_PPM(uint16_t * ppm);

