/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:09:43 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 17:07:04 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

char	*expand_symbol(char *cmd, char **envp, int len);
int		search_expandable(char *cmd);

t_env	*create_env_node(char *env);
t_env	*find_env(t_env **env_head, char *name, int len);
void	addenv(t_env **env_head, char *env);
void	init_envp(t_env **env_head, char **envp);
void	rmv_env(t_env **env_head, char *name);
int		find_env_len(t_env **env_head, char *name, int len);

int		is_equal_sign(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		check_env(char *env);
#endif