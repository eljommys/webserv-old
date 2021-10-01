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
#include <iostream>
#include <stdlib.h>

int main(int argc, char const **argv)
{
	int socket_fd;
	struct sockaddr_in serv_addr;
	int addrlen = sizeof(serv_addr);

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Could not open socket" std::endl;
		exit(EXIT_FAILURE);
	}

	if ()
}
