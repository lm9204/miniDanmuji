/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:24:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/26 15:18:09 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

void	ft_exit(char **input);
int		validate_arguments(char **cmd);
int		ft_cd(t_data *data, char **path);
int		ft_echo(char **cmds);
int		ft_env(t_env **head);
int		ft_pwd(char *data_pwd);
int		ft_export(t_data *data, char **cmd);
int		ft_unset(t_env **head, char **cmd);

#endif