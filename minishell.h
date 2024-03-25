
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:19:57 by yeondcho          #+#    #+#             */
/*   Updated: 2024/03/24 13:49:40 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_list
{
	void	*content;
	int		flag; // 0 : cmd 1: pipe 2: redirect
	void	*next;
}				t_list;

typedef struct s_cmd
{
	char	**cmds; // [0] = cmd [1] = arg [2] = null
}				t_cmd;

typedef struct s_redirect
{
	int		*fd[2];
	char	*file;
}				t_redirect;

typedef struct s_data
{
	char	**envp;
}				t_data;

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

char	*find_needle_in_haystack(char **haystack, char *magnet);
char	*find_needle_pos(char *haystack);
char	**add_needle_to_haystack(char **haystack, char *needle);
char	**init_haystack(char **envp);
char	*init_hay(char *hay);
int		cnt_column_line(char **envp);
char	**rmv_needle_from_haystack(char **haystack, char *magnet);
void	rmv_needle(char **haystack, char *magnet);
int		check_needle(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		is_equal_sign(char *needle);

#endif