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

#include "cozir.h"
#include <zephyr.h>
#include <device.h>
#include <drivers/i2c.h>

const struct device * i2c_device;

#define I2C_DEV "I2C_1"

int init_CozIR()
{
    i2c_device = device_get_binding(I2C_DEV);
    if (!i2c_device) 
    {
        printk("I2C: Device driver not found.\n");
        return -1;
    }
    printk("I2C: Device driver OK.\n");

    int ret = i2c_configure(i2c_device, I2C_SPEED_SET(I2C_SPEED_STANDARD));
    if (ret < 0 )
    {
        printk("I2C Configuration failed\n");
        return ret;
    }
    return 0;
}

int read_CozIR_CO2_PPM(uint16_t * ppm)
{
    uint8_t co2_ppm[2] = {0,0};
    int ret = i2c_burst_read(i2c_device, COZIR_I2C_ADDRESS, COZIR_CO2_LEVEL_REGISTER, &co2_ppm[0], 2);
    if (ret == 0)
    {
        *ppm = co2_ppm[0] << 8 | co2_ppm[1]; 
    }
    else
    {
        printk("i2c_burst_read failed with error: %d\n", ret);
    }
    return ret;
}

