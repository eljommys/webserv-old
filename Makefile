NAME = webserv

MSG = Default commit message
#MSG="message" to change message

all: $(NAME)

$(NAME):
	g++ webserv.cpp -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean $(NAME)

git:
	git add .
	git commit -m "$(MSG)"
	git push
