NAME = webserv
CC = g++
CFLAGS = -Wall -Error -Wextra -c -std=c++98 -pedantic

SRC =	webserv.cpp \
		server.cpp

OBJ =	$(SRC:.cpp=.o)

MSG = Default commit message
#MSG="message" to change message


all: $(NAME)

$(NAME): $(OBJ)
	g++ $(SRC) $(CFLAGS) $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ)

re: fclean $(NAME)

git:
	git add .
	git commit -m "$(MSG)"
	git push
