/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:03:51 by marvin            #+#    #+#             */
/*   Updated: 2021/10/01 20:03:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>

#define PORT 8080

class Server
{
	public:
		int socket_fd, connect_fd;
		struct sockaddr_in address;
		int addrlen;

		Server(){}
		~Server(){}
};

int main(void)
{
	Server	server;
	size_t	len;

	if ((server.socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Could not open socket" << std::endl;
		return (EXIT_FAILURE);
	}

	server.address.sin_family = AF_INET;
	server.address.sin_addr.s_addr = INADDR_ANY;
	server.address.sin_port = htons( PORT );
	for (int i = 0; i < sizeof(server.address.sin_zero); i++)
		server.address.sin_zero[i] = 0;

	if (bind(server.socket_fd, (struct sockaddr *)&(server.address), sizeof(server.address)) < 0)
	{
		std::cerr << "Could not bind socket" << std::endl;
		return (EXIT_FAILURE);
	}
	if (listen(server.socket_fd, 20) < 0)
	{
		std::cerr << "Could not create socket queue" << std::endl;
		return (EXIT_FAILURE);
	}
	while (true)
	{
		if ((server.connect_fd = accept(server.socket_fd, (struct sockaddr *)&(server.address), (socklen_t *)&(server.addrlen))) < 0)
		{
			std::cerr << "Connection refused" << std::endl;
			return (EXIT_FAILURE);
		}
		std::cout << "Connected" << std::endl;
		char buffer[30000] = {0};
		len = recv(server.connect_fd, buffer, 30000, 0);
		std::cout << buffer << std::endl;
	}
	return (EXIT_SUCCESS);
}
