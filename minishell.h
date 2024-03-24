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

#endif