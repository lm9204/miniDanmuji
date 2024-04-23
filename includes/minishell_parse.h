/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:09:43 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/23 13:25:28 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H


char	*checkcmd(t_data *data, char *cmd);
char	*expand_symbol(t_data *data, char *cmd);
char	*search_expand(t_env **head, char *cmd);
int		get_word_len(char *word);
int		expand_len(t_data *data, char *cmd);
int		expand(t_data *data, char *output, char *cmd, char quote);
int		sub_quote_len(char *cmd, char quote);

t_env	*create_env_node(char *env);
t_env	*find_env(t_env **env_head, char *name);
void	addenv(t_env **env_head, char *env);
void	init_envp(t_env **env_head, char **envp);
void	rmv_env(t_env **env_head, char *name);
int		find_env_len(t_env **env_head, char *name);

void	clear_cmds(char **cmds);
void	free_env_list(t_env **head);
char	**list_to_envp(t_env **head);
char	*ft_env_to_char(t_env *env);

int		validate_node_list(t_data *data);

int		is_equal_sign(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		check_env(char *env);
#endif