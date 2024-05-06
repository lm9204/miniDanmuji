CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP -g3
SRCS = parse/token.c parse/symbol.c parse/list.c parse/spliter_utils.c \
		parse/spliter.c parse/parse.c error.c parse/list_val_utils.c \
		parse/init_envp.c parse/find_env.c parse/add_env.c parse/rmv_env.c \
		parse/list_utils.c parse/list_val.c builtin/builtin.c \
		parse/parse_utils.c parse/parse_heredoc.c builtin/ft_export_utils.c \
		parse/parse_redirect.c \
		builtin/ft_echo.c builtin/ft_cd.c builtin/ft_pwd.c builtin/ft_exit.c \
		builtin/ft_unset.c builtin/ft_env.c builtin/ft_export.c \
		exec/child_to_do.c exec/cmd_handler.c exec/execute_main.c exec/execute_util.c \
		exec/first_or_middle_or_last_child.c exec/signal_handler.c \
		exec/signal_ignore.c exec/get_heredoc_input.c \
		exec/parent_to_do.c exec/redirec_handler.c exec/signal_parent.c minishell.c \
		exec/signal_child.c exec/heredoc_pre_handler.c \
		exec/wait_child.c exec/signal_heredoc.c exec/builtin_handler.c \
		exec/preset_to_do.c exec/cmd_handler_util.c exec/heredoc_util.c \
		exec/expand_flag.c exec/redirec_handler_util.c
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