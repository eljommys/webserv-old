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

#include "webserv.hpp"

Server server;

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\r", 1);
		close(server.getServer_fd());
		exit(SIGINT);
	}
}

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cout << "Error: Too many arguments!" << std::endl;
		return (EXIT_FAILURE);
	}
	else if (argc == 2)
		server.setConf(argv[1]);

	show_config(server.getConfig());
//	Only SININT (CTRL+C) can exit cleanly from the process
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGKILL, sig_handler);

	while (server.prepare() == EXIT_FAILURE)
		std::cout << "Retrying..." << std::endl;

	server.exe();

	return (EXIT_SUCCESS);
}
