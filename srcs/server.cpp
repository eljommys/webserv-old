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

Server::Server():addrlen(sizeof(address))
{
	for (int i = 0; i < CONNECT_NUM; i++)
	{
		connect_fd[i].events = 0;
		connect_fd[i].events |= POLLIN;
	}

	config = parse_config("webserv.conf");
}

Server::~Server()
{
	std::cout << "Turning server off." << std::endl;
}

int	Server::setConf(const std::string &str)
{
	std::ifstream			file(str.c_str());
	std::stringstream		content;

	content << file.rdbuf();

	config = parse_config(content.str());
	return (EXIT_SUCCESS);
}

int Server::prepare()
{
	int verdad = 1;

//	Opening socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Could not open socket" << std::endl;
		return (EXIT_FAILURE);
	}
	setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR, &verdad,sizeof(int));

//	Setting address struct
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	for (int i = 0; i < (int)sizeof(address.sin_zero); i++)
		address.sin_zero[i] = 0;

//	Binding socket
	if (bind(server_fd, (struct sockaddr *)&(address), sizeof(address)) < 0)
	{
		std::cerr << "Could not bind socket" << std::endl;
		return (EXIT_FAILURE);
	}

//	Listening to socket_fd
	if (listen(server_fd, MAX_REQUEST) < 0)
	{
		std::cerr << "Could not create socket queue" << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void		response(int fd, struct Petition petition, struct Config config)
{
	std::stringstream	rsp;
	std::stringstream	fileroute;
	fileroute << config.user << petition.route;
	std::ifstream		file(fileroute.str().c_str());

	fileroute.str("");
	fileroute << file.rdbuf();

	rsp << petition.protocol << " 200 OK" << std::endl;
	rsp << "Content-length: " << fileroute.str().size() << std::endl;
	rsp << "Content-Type: text/html" << std::endl << std:: endl;
	rsp << fileroute.str();

	send(fd, rsp.str().c_str(), rsp.str().size(), 0);
}

int	Server::exe()
{
	char	buffer[30000];

	while (true)
	{
//		Setting 5 seconds timeout to array of fds
		if ((connect_fd[0].fd = accept(server_fd, (struct sockaddr *)&(address), (socklen_t *)&(addrlen))) < 0)
		{
			std::cerr << "Connection refused" << std::endl;
			continue;
		}
		else
			std::cout << "Connected" << std::endl << std::endl;
		
		fcntl(connect_fd[0].fd, F_SETFL, fcntl(connect_fd[0].fd, F_GETFL, 0) | O_NONBLOCK);
		if (!poll(connect_fd, CONNECT_NUM, 5000))
		{
			std::cout << "TIMEOUT!" << std::endl;
			continue;
		}

//		Save client's petition in buffer and parsing it
		recv(connect_fd[0].fd, buffer, 30000, 0);
		std::cout << "=====================Petition=====================" << std::endl;
		std::cout << (std::string)buffer << std::endl;
		petition = parse_petition(buffer);

//		Sending server response
		response(connect_fd[0].fd, petition, config);
		close(connect_fd[0].fd);
	}
	return (EXIT_SUCCESS);
}


//	GETTERS

const int			&Server::getServer_fd()
{
	return this->server_fd;
}

const struct pollfd	&Server::getConnect_fd(const int &i)
{
	return connect_fd[i];
}

const struct Config	&Server::getConfig()
{
	return config;
}
