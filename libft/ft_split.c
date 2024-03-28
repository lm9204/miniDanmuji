/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeondcho <yeondcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:37:25 by yeondcho          #+#    #+#             */
/*   Updated: 2023/12/13 16:56:58 by yeondcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

static int		ft_countwords(char const *s, char c);
static char		*ft_cutword(char const *s, char c, int *search_idx);

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		search_idx;
	int		wordcount;

	search_idx = 0;
	wordcount = ft_countwords(s, c);
	result = (char **)ft_calloc(8, wordcount + 1);
	if (result == NULL)
		return (NULL);
	while (s[search_idx] && s[search_idx] == c)
		search_idx++;
	i = -1;
	while (++i < wordcount)
	{
		result[i] = ft_cutword(s, c, &search_idx);
		if (result[i] == NULL)
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
	}
	return (result);
}

static char	*ft_cutword(char const *s, char c, int *search_idx)
{
	char	*word;
	int		wordlen;

	wordlen = 0;
	while (s[wordlen + *search_idx] && s[wordlen + *search_idx] != c)
		wordlen++;
	word = ft_allocword(&s[*search_idx], wordlen);
	if (word == NULL)
		return (NULL);
	while (s[wordlen + *search_idx] && s[wordlen + *search_idx] == c)
		(*search_idx)++;
	*search_idx += wordlen;
	return (word);
}

char	*ft_allocword(char const *s, int size)
{
	char	*word;
	int		i;

	word = (char *)ft_calloc(1, size + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static int	ft_countwords(char const *s, char c)
{
	int	isword;
	int	count;

	isword = 0;
	count = 0;
	while (*s)
	{
		if (!isword && *s != c)
		{
			isword = 1;
			count++;
		}
		if (isword && *s == c)
			isword = 0;
		s++;
	}
	return (count);
}
