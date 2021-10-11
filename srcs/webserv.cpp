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
		close(server.getServer_fd());
		exit(SIGINT);
	}
}

int main(int argc, char **argv)
{
	int ret;

	if (argc > 2)
	{
		std::cout << "Error: Too many arguments!" << std::endl;
		return (EXIT_FAILURE);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGKILL, sig_handler);
	if (argc == 2)
		server.setHome(argv[1]);

	ret = server.prepare();
	ret += server.exe();

	return (ret);
}
