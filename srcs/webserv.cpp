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

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cout << "Error: Too many arguments!" << std::endl;
		return (EXIT_FAILURE);
	}
	Server server;
	if (argc == 2)
		server.setHome(argv[1]);

	server.prepare();
	server.exe();

	return (EXIT_SUCCESS);
}
