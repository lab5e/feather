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
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "modeminfo.h"
#include <modem/lte_lc.h>
#include <modem/modem_info.h>

#define MODEM_INFO_BUFFER_SIZE 32
uint8_t modem_info_buf[MODEM_INFO_BUFFER_SIZE];

bool get_modem_info() 
{
	// Initialize the modem information module
	if (modem_info_init() != 0) 
	{
		printk("Modem info could not be initialized");
		return false;
	}

	// Configure the modem for normal operation mode
	int ret = lte_lc_normal();
	if (ret != 0) 
	{
		printk("lte_lc_normal: %d\n", ret);
		return false;
	}

	// Wait until the SIM card is ready
	while (true) 
	{
		uint16_t uicc_state;
		int len = modem_info_short_get(MODEM_INFO_UICC, &uicc_state);
		if (len <= 0) 
		{
			printk("Failed reading UICC: %d\n", len);
			return false;
		}
		if (uicc_state == 1) 
		{
			break;
		}
		k_sleep(K_SECONDS(1));
	}

	// Retrieve the 15 digit IMEI (required for registering your device in Span)
	memset(modem_info_buf, 0, MODEM_INFO_BUFFER_SIZE);
	int len = modem_info_string_get(MODEM_INFO_IMEI, modem_info_buf, MODEM_INFO_BUFFER_SIZE);
	if (len <= 0) 
	{
		printk("Failed reading IMEI: %d\n", len);
		return false;
	}
	printk("IMEI: %s\n", modem_info_buf);

	// Retrieve the 15 digit IMSI (required for registering your device in Span)
	len = modem_info_string_get(MODEM_INFO_IMSI, modem_info_buf, MODEM_INFO_BUFFER_SIZE);
	if (len <= 0) 
	{
		printk("Failed reading IMSI: %d\n", len);
		return false;
	}
	printk("IMSI: %s\n", modem_info_buf);

	// Put the modem offline
	ret = lte_lc_offline();
	if (ret != 0) 
	{
		printk("lte_lc_offline: %d\n", ret);
		return false;
	}

	return true;
}
