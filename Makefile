ROOT = ./srcs/

PARSER = parser/parser.cpp

NAME = webserv
CXX = g++
#CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic

SRC =	$(ROOT)webserv.cpp \
		$(ROOT)server.cpp \
		$(ROOT)parser/parser.cpp

OBJ =	$(SRC:.cpp=.o)

MSG = Default commit message
#MSG="message" to change message


all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(NAME) parser

fclean: clean
	rm -rf $(OBJ)

re: fclean $(NAME)

git: fclean
	git add .
	git commit -m "$(MSG)"
	git push

parser:
	$(CXX) $(ROOT)$(PARSER) $(ROOT)server.cpp -o parser
