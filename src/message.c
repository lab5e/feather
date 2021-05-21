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

#include <net/socket.h>

bool send_message(const char *message) 
{
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) 
	{
		printk("Error opening socket: %d\n", errno);
		return false;
	}

	static struct sockaddr_in remote_addr = 
	{
		sin_family: AF_INET,
		sin_port:   htons(1234),
	};
	net_addr_pton(AF_INET, "172.16.15.14", &remote_addr.sin_addr);

	if (sendto(sock, message, strlen(message), 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0) 
	{
		printk("Error sending: %d\n", errno);
		close(sock);
		return false;
	}

	close(sock);
	return true;
}
