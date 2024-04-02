/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:57 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:16:38 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define F_CMD 0
# define F_PIPE 1
# define F_DIRECT 2
# define T_INPUT 0
# define T_OUTPUT 1
# define T_HEREDOC 2
# define T_APPEND 3

# include "includes/minishell_parse.h"
# include "includes/minishell_exec.h"

// flag | 0 : cmd 1: pipe 2: redirect
typedef struct s_list
{
	int		flag;
	void	*content;
	void	*next;
}				t_list;

// [0] = cmd [1] = arg [2] = null
typedef struct s_cmd
{
	char	**cmds;
}				t_cmd;

typedef struct s_redirect
{
	int		fd[2];
	int		type;
	char	*file;
}				t_redirect;

typedef struct s_data
{
	char	**envp;
}				t_data;

typedef struct s_env
{
	char	*name;
	char	*value;
	void	*next;
}				t_env;

/* =========================== list.c ===================================*/
void	parse_to_node(t_list **head, char **tokens);
void	clear_head(t_list **head);

// test
void	print_list(t_list **head);
/* ============================ symbol.c ================================*/
int		is_symbol(const char *token);
int		is_word(const char *line);
int		get_pipe_idx(char **tokens);

int		findquotes(char *s, int quote);
int		ft_isquotes(char c);
int		splitable_symbol_len(const char *cmds, int len);

char	**split_cmds(char *cmds, char **envp);


int		find_space(char *cmd);

/* ============================ error.c ================================*/
void	handle_error(char *error);

/* ============================ token.c ================================*/
int		token_cmds_len(char **tokens);
int		tokenlen(char **tokens);

/* ========================== 환경 변수 핸들링===============================*/
char	*find_env(char **envp_2d_ary, char *env);
char	*find_env_pos(char *envp_1d_ary);
char	**add_env(char **envp_2d_ary, char *env);
char	**init_envp(char **envp);
char	*init_one_line(char *line);
char	**rmv_env(char **envp_2d_ary, char *env);
void	rmv_needle(char **haystack, char *magnet);
int		cnt_column_line(char **envp);
int		check_needle(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		is_equal_sign(char *needle);

#endif