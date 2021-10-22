#include "parser.hpp"

struct Petition	parse_petition(std::string buffer)
{
	struct Petition	petition;

	petition.protocol = buffer.substr(buffer.find("HTTP"), buffer.find("\n") - buffer.find("HTTP") - 1);
	std::string		types[] = {"GET", "POST", "DELETE"};
	std::string		method = buffer.substr(0, buffer.find_first_of(' '));
	for (petition.type = GET; method != types[petition.type] && petition.type < 3; petition.type++);

	petition.route = buffer.substr(buffer.find_first_of(' ') + 1, buffer.find(" HTTP") - buffer.find_first_of(' ') - 1);
	if (petition.route == "/")
		petition.route = "/index.html";

	std::cout << "protocol = \"" << petition.protocol << "\"" << std::endl;
	std::cout << "type = " << types[petition.type] << std::endl;
	std::cout << "route = \"" << petition.route << "\"" << std::endl;

	return (petition);
}

struct Config	parse_config(const std::string &str)
{
	struct Config	config;
	std::ifstream	file_stream;

	try{
		file_stream.open(str.c_str(), std::ifstream::in);
	}catch (const std::ifstream::failure &e){
		std::cerr << e.what();
	}

	return config;
}

static void show(struct Config config)
{
	typedef std::vector<int>::iterator it;

	std::cout << "home '" << config.home << "'" << std::endl;
	std::cout << "user '" << config.user << "'" << std::endl;
	std::cout << "index '" << config.index << "'" << std::endl;
	std::cout << "ports";
	for (it i = config.ports.begin(); i < config.ports.end(); i++)
		std::cout << " '" << *i << "'";
	std::cout << std::endl;
}

int main(void)
{
	struct Config config = parse_config("webserv.conf");
	show(config);
}
