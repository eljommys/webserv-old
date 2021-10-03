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

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <fstream>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <poll.h>
//# include "parser.hpp"

# define PORT		8080
# define	GET		0
# define	POST	1
# define	DELETE	2

struct Petition
{
	int			type;
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
		pollfd				connect_fd;
		struct sockaddr_in	address;
		int					addrlen;
		struct Petition		petition;
		struct Config		config;

	public:
		Server();
		~Server(){}
		int	setHome(std::string home);
		int	prepare();
		int	exe();
};

#endif
