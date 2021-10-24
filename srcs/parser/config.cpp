#include "parser.hpp"

std::string		get_first_block(const std::string &name, std::string text)
{
	std::string::iterator i = text.begin() + text.find(name) + name.size();

	i = text.begin() + text.find('{', i - text.begin()) + 1;
	std::string::iterator begin = i;
	for (int j = 1; j > 0 && i < text.end(); i++)
	{
		if (text.find('{', i - text.begin()) < text.find('}', i - text.begin()))
		{
			j++;
			i = text.begin() + text.find('{', i - text.begin());
		}
		else
		{
			j--;
			i = text.begin() + text.find('}', i - text.begin());
		}
	}
	return text.substr(begin - text.begin(), i - begin - 1);
}

std::string		get_value(const std::string &name, std::string text)
{
	std::string::iterator begin = text.begin() + text.find(name) + name.size();
	std::string::iterator end;
	while (0 < *(begin.base()) && *(begin.base()) < 33)
		begin++;
	if (text.find('{', begin - text.begin()) < text.find(';', begin - text.begin()))
		end = text.begin() + text.find('{', begin - text.begin());
	else
		end = text.begin() + text.find(';', begin - text.begin());
	while (*((end - 1).base()) == ' ')
		end--;								//revisar
	return text.substr(begin - text.begin(), end - begin);
}

std::vector<std::string>	get_vector(std::string str)
{
	std::vector<std::string>	vector;
	int							j = 0;
	std::string::iterator		i = str.begin();

	std::cout << "str = " << str << std::endl;
	while (i < str.end())
	{
		while (*(i.base()) == ' ')
			i++;
		std::cout << "next space is " << str.find(' ', i - str.begin()) << std::endl;
		if (str.find(' ', i - str.begin()) != std::string::npos)
			vector.push_back(str.substr(i - str.begin(), str.find(' ', i - str.begin()) - (int)(i - str.begin())));
		else
			vector.push_back(str.substr(i - str.begin(), str.end() - i));
		std::cout << "vector[" << j << "] = ->" << vector[j] << "<-" << std::endl;
		i += vector[j].size();
		j++;
	}
	return vector;
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

	std::stringstream stream;
	stream << file_stream.rdbuf();
	std::string text(stream.str().c_str());

	for (char j = 1; j < 31 && j != '\t'; j++)
		text.erase(std::remove(text.begin(), text.end(), j), text.end());
	text.erase(std::remove(text.begin(), text.end(), 127), text.end());
	std::replace(text.begin(), text.end(), '\t', ' ');

	std::string begin = text;
	std::string::iterator i = text.begin();

	config.user = get_value("user", text.begin().base());
	text = get_first_block("http", text);
	config.index = get_vector(get_value("index", text));

	int j = 0;
	std::string t_server = get_first_block("server", text);
	while (t_server[0])
	{
		struct V_server	server;
		std::stringstream num(get_value("listen", t_server));
		num >> server.port;
		server.server_names = get_vector(get_value("server_name", t_server));
		int k = 0;
		std::string t_location = get_first_block("location", t_server);
		while (t_location[0])
		{
			struct Location location;
			location.path = get_value("location", text);
			location.autoindex = (get_value("autoindex", t_server) == "on") ? true : false;
			location.root = get_value("root", t_server);
			server.location.push_back(location);
			t_server = (t_server.begin() + t_location.size()).base(); //PROBABLEMENTE ESTO DE PROBLEMAS (EL CONTENDIDO DEL BLOQUE NO ES LO QUE MIDE ENTERAMENTE)
		}
		config.servers.push_back(server);
		text = (text.begin() + t_server.size()).base();
		t_server = get_first_block("server", text);
	}

	return config;
}
