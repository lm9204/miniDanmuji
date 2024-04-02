/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:09:43 by yeondcho          #+#    #+#             */
/*   Updated: 2024/04/02 15:16:34 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
# define MINISHELL_PARSE_H


char	*expand_symbol(char *symbol, char **envp, int len);
int		search_expandable(char *cmd);

#endif