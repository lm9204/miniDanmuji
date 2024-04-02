CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
SRCS = parse/token.c parse/symbol.c parse/list.c parse/spliter_utils.c \
		parse/spliter.c parse/parse.c error.c \
		parse/init_envp.c parse/find_env.c parse/add_env.c parse/rmv_env.c
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