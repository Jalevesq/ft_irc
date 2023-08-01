NAME = irc

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

#CFLAGS = -std=c++98

RM = rm -rf

SRC =	main.cpp \
			./srcs/Server.cpp \
			./srcs/User.cpp \
			./srcs/Command.cpp \
			./srcs/Nickname.cpp \
			./srcs/Join.cpp \
			./srcs/Ping.cpp \
			./srcs/Username.cpp \
			./srcs/CommandFactory.cpp \
			./srcs/Channel.cpp \
			./srcs/Utility.cpp \
			./srcs/Pass.cpp \
			./srcs/Part.cpp \
			./srcs/Privmsg.cpp \
			./srcs/Topic.cpp

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
	 valgrind --leak-check=yes ./$(NAME) $(PORT)

docker:
	 docker run -ti weechat/weechat

.PHONY: all clean re fclean run leaks docker