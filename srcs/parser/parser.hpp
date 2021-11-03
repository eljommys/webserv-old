/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:09:16 by marvin            #+#    #+#             */
/*   Updated: 2021/10/03 22:09:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../webserv.hpp"

struct Petition	parse_petition(std::string, struct Config config);
struct Config	parse_config(const std::string &);

void show_config(struct Config config);
void show_petition(struct Petition petition);
