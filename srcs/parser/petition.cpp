#include "parser.hpp"


//	GET / HTTP/1.1
//	Host: localhost:8080
//	Connection: keep-alive
//	Cache-Control: max-age=0
//	sec-ch-ua: "Google Chrome";v="95", "Chromium";v="95", ";Not A Brand";v="99"
//	sec-ch-ua-mobile: ?0
//	sec-ch-ua-platform: "Windows"
//	Upgrade-Insecure-Requests: 1
//	User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36
//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
//	Sec-Fetch-Site: none
//	Sec-Fetch-Mode: navigate
//	Sec-Fetch-User: ?1
//	Sec-Fetch-Dest: document
//	Accept-Encoding: gzip, deflate, br
//	Accept-Language: en-US,en;q=0.9,es-ES;q=0.8,es;q=0.7

//	GET /404_not_found/style.css HTTP/1.1
//	Host: localhost:8080
//	Connection: keep-alive
//	sec-ch-ua: "Google Chrome";v="95", "Chromium";v="95", ";Not A Brand";v="99"
//	sec-ch-ua-mobile: ?0
//	User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36
//	sec-ch-ua-platform: "Windows"
//	Accept: text/css,*/*;q=0.1
//	Sec-Fetch-Site: same-origin
//	Sec-Fetch-Mode: no-cors
//	Sec-Fetch-Dest: style
//	Referer: http://localhost:8080/
//	Accept-Encoding: gzip, deflate, br
//	Accept-Language: en-US,en;q=0.9,es-ES;q=0.8,es;q=0.7

//	GET /404_not_found/script.js HTTP/1.1
//	Host: localhost:8080
//	Connection: keep-alive
//	sec-ch-ua: "Google Chrome";v="95", "Chromium";v="95", ";Not A Brand";v="99"
//	sec-ch-ua-mobile: ?0
//	User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36
//	sec-ch-ua-platform: "Windows"
//	Accept: */*
//	Sec-Fetch-Site: same-origin
//	Sec-Fetch-Mode: no-cors
//	Sec-Fetch-Dest: script
//	Referer: http://localhost:8080/
//	Accept-Encoding: gzip, deflate, br
//	Accept-Language: en-US,en;q=0.9,es-ES;q=0.8,es;q=0.7

/* static bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
} */

static std::string		get_value(const std::string &petition, std::string str)
{
	str += ": ";
	if (petition.find(str) == std::string::npos)
		return "";
	int begin = petition.find(str) + str.size();
	int end = petition.find('\n', begin);
	return (petition.substr(begin, end - begin));
}

struct Petition	parse_petition(std::string buffer, struct Config config)
{
	struct Petition	petition;
	struct stat		file_type;

	petition.protocol = buffer.substr(buffer.find("HTTP"), buffer.find("\n") - buffer.find("HTTP") - 1);
	petition.is_first = (get_value(buffer, "Cache-Control").size()) ? false : true;

	std::string		types[] = {"GET", "POST", "DELETE"};
	std::string		method = buffer.substr(0, buffer.find_first_of(' '));
	for (petition.type = GET; method != types[petition.type] && petition.type < 3; petition.type++);

	petition.route = config.user + buffer.substr(buffer.find_first_of(' ') + 1, buffer.find(" HTTP") - buffer.find_first_of(' ') - 1);
	petition.accept = get_value(buffer, "Accept");

	if (petition.route == config.user + "/")
		petition.route = config.user + "/" + config.home;
	errno = 0;
	stat(petition.route.c_str(), &file_type);
	if (errno == ENOENT)
		petition.route = config.user + "/" + config.error_file + "/" + "index.html";
	else if (S_ISDIR(file_type.st_mode))
	{
		for (int i = 0; i < (int)config.index.size(); i++)
		{
			std::string fileroute = petition.route + "/" + config.index[i];
			errno = 0;
			stat(fileroute.c_str(), &file_type);
			if (errno == 0)
			{
				petition.route = fileroute;
				break;
			}
		}
	}

	return (petition);
}
