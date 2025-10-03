/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:14:40 by adavitas          #+#    #+#             */
/*   Updated: 2025/10/01 19:14:41 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	w;

	w = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			w++;
		while (*s && *s != c)
			s++;
	}
	return (w);
}

static char	*next_word(const char **s, char c)
{
	const char	*start;
	size_t		len;
	char		*word;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	word = malloc(len + 1);
	if (word)
		ft_strlcpy(word, start, len + 1);
	return (word);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		w;
	char	**res;

	if (!s)
		return (NULL);
	i = 0;
	w = count_words(s, c);
	res = malloc((w + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < w)
	{
		res[i] = next_word(&s, c);
		if (!res[i])
		{
			while (i > 0)
				free(res[--i]);
			free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
