/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_type.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:23:50 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/12 16:40:24 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPE_H
# define MINISHELL_TYPE_H

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

// [<<] = 0  [>>] = 1  [<] = 2  [>] = 3  [<< -> <] = 4
typedef struct s_redirect
{
	int		fd[2];
	int		type;
	char	*file;
}				t_redirect;

typedef struct s_env
{
	char	*name;
	char	*value;
	void	*next;
}				t_env;

typedef struct s_data
{
	char	*home; //pwd 저장할 거
	char	**splitted_exec_path;
	t_env	**env_head;
}				t_data;

#endif