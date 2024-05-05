/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:09:43 by yeondcho          #+#    #+#             */
/*   Updated: 2024/05/05 20:10:30 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H

char	*checkcmd(t_data *data, char *cmd, int *quote_flag);
char	*expand_symbol(t_data *data, char *cmd);
char	*search_expand(t_env **head, char *cmd);
int		get_word_len(char *word);
int		expand_len(t_data *data, char *cmd);
int		expand(t_data *data, char *output, char *cmd, int quote);

t_env	*create_env_node(char *env);
t_env	*find_env(t_env **env_head, char *name);
void	addenv(t_env **env_head, char *env);
void	init_envp(t_env **env_head, char **envp);
void	rmv_env(t_env **env_head, char *name);
int		find_env_len(t_data *data, char *name);

void	clear_cmds(t_cmd *cmd);
void	free_env_list(t_env **head);
char	**list_to_envp(t_env **head);
char	*ft_env_to_char(t_env *env);

char	**split_cmds_space(t_cmd *cmd, int og_size);
int		validate_node_list(t_data *data);
void	expand_node(t_data *data, t_cmd *cmds);

int		is_equal_sign(char *needle);
int		front_or_back_of_equal_sign(char *needle);
int		check_env(char *env);

void	free_cmds(char **cmds);
int		is_expandable(char *word);
char	*cut_expand(char *cmd);
char	*heredoc_newline(t_data *data, char *cmd);
int		expand_join(t_data *data, char *expand, char *output, int *i);
char	*rmv_quotes(char *cmd);

char	*parse_redir(t_data *data, char *cmd, int *redir_flag);

#endif