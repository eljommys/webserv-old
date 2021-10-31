#include "parser.hpp"

void show(struct Config config)
{
	std::cout << "user '" << config.user << "'" << std::endl;
	std::cout << "index ";
	for (std::vector<std::string>::iterator j = config.index.begin(); j < config.index.end(); j++)
			std::cout << " '" << *j << "'";
	std::cout << std::endl;
	std::cout << "error '" << config.error_file << "'" << std::endl;
	std::cout << "body_size '" << config.max_body_size << "'" << std::endl;
	for (std::vector<struct V_server>::iterator i = config.servers.begin(); i < config.servers.end(); i++)
	{
		std::cout << std::endl;
		std::cout << "Server #" << i - config.servers.begin() << std::endl;
		std::cout << "\tPort" << i->port << std::endl;
		std::cout << "\tServer Names";
		for (std::vector<std::string>::iterator j = i->server_names.begin(); j < i->server_names.end(); j++)
			std::cout << " '" << *j << "'";
		std::cout << std::endl;
		for (std::vector<struct Location>::iterator j = i->location.begin(); j < i->location.end(); j++)
		{
			std::cout << "\tLocation " << j->path << std::endl;
			std::cout << "\t\tMethods";
			for (std::vector<std::string>::iterator k = j->methods.begin(); k < j->methods.end(); k++)
				std::cout << " '" << *k << "'";
			std::cout << std::endl;
			std::cout << "\t\tAutoindex " << j->autoindex << std::endl;
			std::cout << "\t\tRoot " << j->root << std::endl;
		}
	}
	std::cout << std::endl;
}

static bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

struct Petition	parse_petition(std::string buffer, struct Config config)
{
	struct Petition	petition;

	petition.protocol = buffer.substr(buffer.find("HTTP"), buffer.find("\n") - buffer.find("HTTP") - 1);
	std::string		types[] = {"GET", "POST", "DELETE"};
	std::string		method = buffer.substr(0, buffer.find_first_of(' '));
	for (petition.type = GET; method != types[petition.type] && petition.type < 3; petition.type++);

	petition.route = config.user + buffer.substr(buffer.find_first_of(' ') + 1, buffer.find(" HTTP") - buffer.find_first_of(' ') - 1);

	if (petition.route[petition.route.size() - 1] == '/')
	{
		for (int i = 0; i < (int)config.index.size(); i++)
		{
			std::string fileroute = petition.route + config.index[i];
			if (file_exists(fileroute) == true)
			{
				petition.route = fileroute;
				break;
			}
		}
	}
	if (file_exists(petition.route) == false || petition.route[petition.route.size() - 1] == '/')
		petition.route = config.user + "/" + config.error_file + "/" + "index.html";

	std::cout << "protocol = \"" << petition.protocol << "\"" << std::endl;
	std::cout << "type = " << types[petition.type] << std::endl;
	std::cout << "route = \"" << petition.route << "\"" << std::endl;

	return (petition);
}

/* int main(void)
{
	struct Config config = parse_config("webserv.conf");
	show(config);
} */
