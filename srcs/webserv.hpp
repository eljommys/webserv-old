/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:32:50 by marvin            #+#    #+#             */
/*   Updated: 2021/10/03 19:32:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/socket.h>
# include <netinet/in.h>
# include <signal.h>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstdio>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <poll.h>
# include "parser.hpp"

# define	PORT	8080
# define	GET		0
# define	POST	1
# define	DELETE	2

# define	CONNECT_NUM	1
# define	MAX_REQUEST	5

struct Petition
{
	int			type;
	std::string	protocol;
	std::string	route;
};

struct Config
{
	std::string	home;
	std::string	user;
	std::string	index;
	int			*ports;
};

class Server
{
	private:
		int 				server_fd;
		struct pollfd		connect_fd[CONNECT_NUM];
		struct sockaddr_in	address;
		int					addrlen;
		struct Petition		petition;
		struct Config		config;

	public:
		Server();
		~Server();
		int	setConf(const std::string &);
		int	prepare();
		int	exe();

		const int			&getServer_fd();
		const struct pollfd	&getConnect_fd(const int &);
};
