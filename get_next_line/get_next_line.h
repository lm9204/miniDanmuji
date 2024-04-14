/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjko <seongjko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:42:54 by seongjko          #+#    #+#             */
/*   Updated: 2024/02/17 19:45:58 by seongjko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*line(char **rest, int fd);
char	*cut(char **rest, int new_pos, int i);
char	*gnl_strrest(char *buff, int new_pos);
int		gnl_strchr(const char *s, int c);
char	*gnl_strndup(char *str, int len);
char	*gnl_strjoin(char *dest, char *append);
size_t	gnl_strlen(const char *str);

#endif