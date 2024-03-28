/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:01:50 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/26 18:45:17 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_gnl	*lst;
	t_gnl			*node;
	char			*result;

	result = NULL;
	node = lstschfd(&lst, fd);
	if (node == NULL)
	{
		node = lstaddnew(&lst, fd);
		if (node == NULL)
			return (NULL);
	}
	result = alloc_line(node, BUFFER_SIZE);
	if (result == NULL)
		delnode(&lst, fd);
	return (result);
}

// NON_NL : NO NL, EOF_G : EOF
int	check_buffer(char *buf)
{
	int	i;
	int	buf_len;

	i = 0;
	buf_len = ft_strlen(buf);
	while (i < buf_len)
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (NON_NL);
}

char	*alloc_line(t_gnl *node, int len)
{
	char	*rem;
	char	*tmp;

	if (node->nl_idx == READ_ERROR)
		return (NULL);
	if (node->nl_idx == EOF_G)
	{
		if (check_buffer(node->buf) == NON_NL)
			return (split_nl(node, ft_strlen(node->buf) - 1));
		return (split_nl(node, check_buffer(node->buf)));
	}
	node->nl_idx = check_buffer(node->buf);
	if (node->nl_idx != NON_NL)
		return (split_nl(node, node->nl_idx));
	rem = node->buf;
	fill_buffer(node, &node->buf, 0, len);
	tmp = ft_strjoin(rem, node->buf);
	free(node->buf);
	free(rem);
	node->buf = tmp;
	return (alloc_line(node, len * 2));
}

void	fill_buffer(t_gnl *node, char **buf, int cur_len, int read_size)
{
	ssize_t	readen_size;

	if (cur_len == 0)
	{
		*buf = malloc(sizeof(char) * (read_size + 1));
		if (*buf == NULL)
			return ;
		(*buf)[read_size] = 0;
	}
	if (cur_len == read_size)
		return ;
	readen_size = read(node->fd, &(*buf)[cur_len], BUFFER_SIZE);
	(*buf)[cur_len + readen_size] = 0;
	if (readen_size > 0 && check_buffer(*buf) == NON_NL)
		fill_buffer(node, buf, cur_len + readen_size, read_size);
	if (readen_size == -1)
		node->nl_idx = READ_ERROR;
	if (readen_size == 0)
	{
		node->nl_idx = EOF_G;
		(*buf)[cur_len] = 0;
	}
	return ;
}

char	*split_nl(t_gnl *node, int nl_idx)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	if (node->nl_idx == EOF_G && ft_strlen(node->buf) == 0)
		return (NULL);
	result = malloc(sizeof(char) * (nl_idx + 2));
	if (result == NULL)
		return (NULL);
	while (node->buf[i] && i <= nl_idx)
	{
		result[i] = node->buf[i];
		i++;
	}
	result[i] = 0;
	tmp = node->buf;
	node->buf = ft_strjoin(NULL, &node->buf[i]);
	free(tmp);
	return (result);
}
