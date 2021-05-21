/*
	Copyright [2019] [Exploratory Engineering]
	Modifications Copyright [2021] [Lab5e AS]

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

#include <zephyr.h>
#include <errno.h>
#include <stdio.h>
#include "cozir.h"
#include "modeminfo.h"
#include <modem/lte_lc.h>
#include "message.h"


// If you haven't already registered your device in Span, you should undefine this
// and connect a terminal emulator before running the sample. 
// The IMEI and IMSI numbers will then be displayed on the console. Copy and use
// these numbers in the "Add new device" dialog in Span.
#define MODULE_IS_ALREADY_REGISTERED_IN_SPAN 1

void main() 
{
	printk("Feather CozIR sample started\n"); 

#if !(MODULE_IS_ALREADY_REGISTERED_IN_SPAN)
	get_modem_info();
#endif

	// Initialize and configure the modem
    int err = lte_lc_init();
    if (err != 0) {
        printk("lte_lc_init failed: %d\n", err);
        return;
    }

	// Initialize and configure the modem
	printk("Connecting to mda.lab5e...\n"); 
	err = lte_lc_connect();
	if (err != 0) 
	{
		printk("lte_lc_connect failed: %d\n", err);
		return;
	}

	// Initialize I2C and the CozIR sensor
    init_CozIR();

    uint16_t ppm;
    int seconds = 0;
    char messagebuffer[32];
    while (true)
    {
        k_sleep(K_SECONDS(1));
        seconds++;

		// Get the CO2 concentration from the sensor in parts per million
        read_CozIR_CO2_PPM(&ppm);
        printk("PPM CO2: %d\n", ppm);

		// Transmit every ten seconds. If you are on a limited data subscription plan, 
		// you may want to increase this delay :)
        if (seconds % 10 == 0)
        {
			// For the sake of clarity, we'll encode a text string. In a real world
			// application you would want to send the raw binary value instead and
			// decode this where you want to access the data.
            sprintf(messagebuffer, "CO2: %d ppm", ppm);
        	if (send_message(messagebuffer)) 
            {
        		printk("Message sent ok!\n"); 
	        } else {
		        printk("Failed to send message\n");
            }
        }
    }
}
