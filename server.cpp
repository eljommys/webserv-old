/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:34:21 by marvin            #+#    #+#             */
/*   Updated: 2021/10/03 19:34:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

Server::Server():addrlen(sizeof(address)), home("./"){}

int	Server::setHome(std::string home)
{
	this->home = home;
	return (EXIT_SUCCESS);
}

int Server::prepare()
{
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Could not open socket" << std::endl;
		return (EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	for (int i = 0; i < sizeof(address.sin_zero); i++)
		address.sin_zero[i] = 0;

	if (bind(server_fd, (struct sockaddr *)&(address), sizeof(address)) < 0)
	{
		std::cerr << "Could not bind socket" << std::endl;
		return (EXIT_FAILURE);
	}
	if (listen(server_fd, 20) < 0)
	{
		std::cerr << "Could not create socket queue" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static struct Petition	parser(std::string buffer)
{
	struct Petition	petition;

	std::string		types[] = {"GET", "POST", "DELETE"};
	std::string		method = buffer.substr(0, buffer.find_first_of(' '));
	for (petition.type = GET; method != types[petition.type] && petition.type < 3; petition.type++);

	petition.route = buffer.substr(buffer.find_first_of(' ') + 1, buffer.find(" HTTP") - buffer.find_first_of(' ') - 1);

	std::cout << "type = " << petition.type << std::endl;
	std::cout << "route = \"" << petition.route << "\"" << std::endl;

	return (petition);
}

int	Server::exe()
{
	while (true)
	{
		if ((connect_fd.fd = accept(server_fd, (struct sockaddr *)&(address), (socklen_t *)&(addrlen))) < 0)
		{
			std::cerr << "Connection refused" << std::endl;
			return (EXIT_FAILURE);
		}
		std::cout << "Connected" << std::endl << std::endl;
		char buffer[30000] = {0};
		poll(&connect_fd, 20, 2000);

		for (int i = 0; i < 20 && recv(connect_fd.fd, buffer, 30000, 0) >= 0; i++)
		{
			std::cout << "=====================Petition=====================" << std::endl;
			std::cout << (std::string)buffer << std::endl;
			petition = parser(buffer);
		if (petition.type < 0)
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
