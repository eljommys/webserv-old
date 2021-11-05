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
# include <fcntl.h>
# include <iostream>
# include <vector>
# include <algorithm>
# include <fstream>
# include <sstream>
# include <istream>
# include <cstdio>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <poll.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "parser/parser.hpp"

# define	PORT	8080
# define	GET		0
# define	POST	1
# define	DELETE	2

# define	CONNECT_NUM	1
# define	MAX_REQUEST	5

struct Petition
{
	int			type;
	bool		is_first;
	std::string	protocol;
	std::string	route;
	std::string	accept;
};

struct Response
{
	int			code;
	std::string	route;
	int			length;
	std::string type;
};

struct Location
{
	std::string					path;
	std::vector<std::string>	methods;
	bool						autoindex;
	std::string					root;
};

struct V_server
{
	int								port;
	std::vector<std::string>		server_names;
	std::vector<struct Location>	location;
};

struct Config
{
	std::string						user;
	std::vector<std::string>		index;
	std::string						home;
	std::string						error_file;
	int								max_body_size;
	std::vector<struct V_server>	servers;
};

class Server
{
	private:
		std::string			root;
		int 				server_fd;
		struct pollfd		connect_fd[CONNECT_NUM];
		struct sockaddr_in	address;
		int					addrlen;
		struct Config		config;
		struct Petition		petition;

	public:
		Server();
		~Server();
		int	setConf(const std::string &);
		int	prepare();
		int	exe();

		const int				&getServer_fd();
		const struct pollfd		&getConnect_fd(const int &);
		const struct Config		&getConfig();
		const struct Petition	&getPetition();
};
