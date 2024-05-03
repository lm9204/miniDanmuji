/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:57 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/03 16:37:07 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
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
# define PROMPT_MSG "Danmoujishell: "
# include "includes/minishell_type.h"
# include "includes/minishell_parse.h"
# include "includes/minishell_exec.h"
# include "includes/minishell_builtin.h"

/* =========================== list.c ===================================*/
void	parse_to_node(t_list **head, char **tokens);
void	clear_head(t_list **head);

// test
void	print_list(t_list **head);
/* ============================ symbol.c ================================*/
int		is_symbol(const char *token);
int		is_word(const char *line);
int		get_pipe_idx(char **tokens);

int		findquotes(const char *s, int quote);
int		ft_isquotes(char c);
int		splitable_symbol_len(const char *cmds, int len);

char	**split_cmds(char *cmds);
int		find_space(char *cmd);

/* ============================ error.c ================================*/
void	handle_error(char *error);

/* ============================ token.c ================================*/
int		token_cmds_len(char **tokens);
int		tokenlen(char **tokens);

#endif