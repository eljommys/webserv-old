#include "parser.hpp"

struct Petition	parser(std::string buffer)
{
	struct Petition	petition;

	std::string		types[] = {"GET", "POST", "DELETE"};
	std::string		method = buffer.substr(0, buffer.find_first_of(' '));
	for (petition.type = GET; method != types[petition.type] && petition.type < 3; petition.type++);

	petition.route = buffer.substr(buffer.find_first_of(' ') + 1, buffer.find(" HTTP") - buffer.find_first_of(' ') - 1);

	std::cout << "type = " << petition.type << std::endl;
	std::cout << "route = \"" << petition.route << "\"" << std::endl;

	return (petition);
}
