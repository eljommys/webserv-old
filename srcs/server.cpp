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

static int parse_conf(std::ifstream &conf)
{
	std::cout << conf.rdbuf() << std::endl;
	return (EXIT_SUCCESS);
}

Server::Server():addrlen(sizeof(address))
{
	std::ifstream	conf("webserv.conf");

	//parse_conf(conf, *this);
	//parse_conf(conf);
}

int	Server::setHome(std::string route_conf)
{
	std::ifstream	conf(route_conf.c_str());

	//return (parse_conf(conf, *this));
	return (parse_conf(conf));
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
	for (int i = 0; i < (int)sizeof(address.sin_zero); i++)
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
		std::cout << "Returning index.html" << std::endl;

		char buff[10000];
		FILE *index = fopen("../www/index.html", "r");

		fread(buff, sizeof(char), 10000, index);
		std::string text(buff);
		std::cout << text << std::endl;			//================segfault
		//std::ifstream html("../www/index.html");

		//std::cout << html.rdbuf() << std::endl;
		//std::stringstream text;

		//text << html.rdbuf();
		//write(1, text.str().c_str(), text.str().size());
		//send(connect_fd.fd, text.str().c_str(), text.str().size(), 0);
		}
	}
	return (EXIT_SUCCESS);
}
