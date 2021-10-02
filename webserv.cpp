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
	private:
		int socket_fd, connect_fd;
		struct sockaddr_in address;
		int addrlen;

	public:
		Server();
		~Server();

		int					getSocket();
		int					getConnection();
		struct sockaddr_in	&getAddress();
		int					&getAddrlen();
};

Server::Server():addrlen(sizeof(address))
{
	
}

int main(void)
{
	int socket_fd, connection;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Could not open socket" << std::endl;
		return (EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	for (int i = 0; i < sizeof(address.sin_zero); i++)
		address.sin_zero[i] = 0;

	if (bind(socket_fd, (struct sockaddr *)&address, addrlen) < 0)
	{
		std::cerr << "Could not bind socket" << std::endl;
		return (EXIT_FAILURE);
	}
	if (listen(socket_fd, 20) < 0)
	{
		std::cerr << "Could not create socket queue" << std::endl;
		return (EXIT_FAILURE);
	}
	while (true)
	{
		if ((connection = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			std::cerr << "Connection refused" << std::endl;
			return (EXIT_FAILURE);
		}


	}
}
