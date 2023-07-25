NAME = irc

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

#CFLAGS = -std=c++98

RM = rm -rf

SRC =	main.cpp \
			./srcs/Server.cpp \
			./srcs/User.cpp

OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
		$(RM) ${OBJS}

fclean:clean
		$(RM) $(NAME)

re:fclean all

ifndef PORT
PORT = 6667
endif

run:all
	@printf "Running on this ip \033[0;32m"
	@hostname
	@printf "\033[0;37m"
	./$(NAME) $(PORT)
#add password later

leaks:all
	 valgrind --leak-check=yes ./$(NAME) 6667

docker:
	 docker run -ti weechat/weechat

.PHONY: all clean re fclean run leaks docker