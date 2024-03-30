CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
SRCS = token.c symbol.c list.c spliter_utils.c spliter.c parse.c error.c
LIB_DIR = libft
LIB_HEADER = libft.h
LIB = libft.a
OBJS = $(SRCS:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS) $(LIB_DIR)/$(LIB)
	$(CC) $(FLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB) :
	make -C $(LIB_DIR)

$(LIB_DIR) :
	$(MAKE) -C $@ fclean

clean : $(LIB_DIR)
	rm -rf $(OBJS)
	rm -rf $(SRCS:.c=.d)
	rm -rf .mandatory

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean re fclean $(LIB_DIR)