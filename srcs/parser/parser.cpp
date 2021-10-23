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

	std::string line;
	while (std::getline(file_stream, line))
		std::cout << line << std::end

	/* std::stringstream stream;
	stream << file_stream.rdbuf();
	std::string text(stream.str().c_str());

	text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());
	text.erase(std::remove(text.begin(), text.end(), '\r'), text.end());
	text.erase(std::remove(text.begin(), text.end(), '\t'), text.end());

	std::string::iterator i = text.begin();
	i += text.find_first_of("user");
	i += i.base().find_first_not_of("user");
	std::cout << i.base() << std::endl; */

	return config;
}

static void show(struct Config config)
{
	std::cout << "home '" << config.home << "'" << std::endl;
	std::cout << "user '" << config.user << "'" << std::endl;
	std::cout << "index '" << config.index << "'" << std::endl;
	for (std::vector<struct V_server>::iterator i = config.servers.begin(); i < config.servers.end(); i++)
	{
		std::cout << std::endl;
		std::cout << "Server #" << i - config.servers.begin() << std::endl;
		std::cout << "\tPort" << i->port << std::endl;
		std::cout << "\tServer Names";
		for (std::vector<std::string>::iterator j = i->server_names.begin(); j < i->server_names.end(); j++)
			std::cout << " '" << *j << "'";
		std::cout << std::endl;
		std::cout << "\tLocation" << std::endl;
		std::cout << "\t\tPath";
		for (std::vector<std::string>::iterator j = i->location.path.begin(); j < i->location.path.end(); j++)
			std::cout << " '" << *j << "'";
		std::cout << std::endl;
		std::cout << "\t\tMethods";
		for (std::vector<std::string>::iterator j = i->location.path.begin(); j < i->location.path.end(); j++)
			std::cout << " '" << *j << "'";
		std::cout << std::endl;
		std::cout << "\t\tAutoindex " << i->location.autoindex << std::endl;
		std::cout << "\t\tIndex";
		for (std::vector<std::string>::iterator j = i->location.index.begin(); j < i->location.index.end(); j++)
			std::cout << " '" << *j << "'";
	}
	std::cout << std::endl;
}

int main(void)
{
	struct Config config = parse_config("webserv.conf");
	show(config);
}
