/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:24:31 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/16 20:44:06 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

void	ft_cd(t_data *data, char *path);
void	ft_echo(char **cmds);
void	ft_exit(char *input);
void	ft_env(t_env **head);
void	ft_pwd(char *data_pwd);
void	ft_export(t_env **head, char **cmd);
void	ft_unset(t_env **head, char **cmd);

#endif