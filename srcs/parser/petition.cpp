#include "parser.hpp"

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

	if (petition.route == config.user + "/")
		petition.route = config.user + "/" + config.home;
		//petition.route[petition.route.size() - 1] == '/'
	if (petition.route.find_last_of('.') == std::string::npos)
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
	if (file_exists(petition.route) == false || petition.route.find_last_of('.') == std::string::npos)
		petition.route = config.user + "/" + config.error_file + "/" + "index.html";

	std::cout << "protocol = \"" << petition.protocol << "\"" << std::endl;
	std::cout << "type = " << types[petition.type] << std::endl;
	std::cout << "route = \"" << petition.route << "\"" << std::endl;

	return (petition);
}