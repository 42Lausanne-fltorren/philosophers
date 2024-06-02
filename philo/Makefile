NAME		= philo

CC			= gcc
UNAME 		:= $(shell uname -s)

CC_FLAGS	= -Wall -Wextra -Werror -g
INCLUDES	= -Iincludes -Ilibft/includes -lreadline

SRC_DIR		= src
SRC			= main.c \
			  utils.c routine.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

all: $(NAME)

$(NAME):
	$(CC) $(CC_FLAGS) -o $(NAME) $(SRCS) $(INCLUDES) $(OS_FLAGS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

.PHONY: clean fclean re all