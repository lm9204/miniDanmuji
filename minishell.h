/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:57 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/25 11:41:53 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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


/* =========================== list.c ===================================*/
void	parse_to_node(t_list **head, char **tokens);

// test
void	print_list(t_list **head);
/* ============================ symbol.c ================================*/
int		is_symbol(char *token);
int		get_symbol_idx(char **tokens);


/* ========================== 환경 변수 핸들링===============================*/
char	*find_needle_in_haystack(char **haystack, char *magnet);
char	*find_needle_pos(char *haystack);
char	**add_needle_to_haystack(char **haystack, char *needle);
char	**init_haystack(char **envp);
char	*init_hay(char *hay);
char	**rmv_needle_from_haystack(char **haystack, char *magnet);
void	rmv_needle(char **haystack, char *magnet);
int		cnt_column_line(char **envp);
int		check_needle(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		is_equal_sign(char *needle);

#endif