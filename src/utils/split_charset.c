/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:26:08 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:58 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delim(char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	word_num(const char *s, const char *set, int *i, int *j)
{
	int	k;
	int	n;

	k = 0;
	n = 0;
	*i = -1;
	*j = 0;
	while (s[k])
	{
		while (s[k] && is_delim(s[k], set))
			k++;
		if (s[k] && !is_delim(s[k], set))
			n++;
		while (s[k] && !is_delim(s[k], set))
			k++;
	}
	return (n);
}

static int	word_len(const char *s, const char *set)
{
	int	i;

	i = 0;
	while (s[i] && !is_delim(s[i], set))
		i++;
	return (i);
}

static char	**free_arrays(char **splitted, int i)
{
	int		j;

	j = -1;
	while (++j < i)
		free(splitted[j]);
	free(splitted);
	return (NULL);
}

char	**ft_split_charset(const char *s, const char *set)
{
	char	**splitted;
	int		words;
	int		i;
	int		j;
	int		len;

	if (!s || !set)
		return (NULL);
	words = word_num(s, set, &i, &j);
	splitted = malloc((words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[words] = 0;
	while (++i < words)
	{
		while (s[j] && is_delim(s[j], set))
			j++;
		len = word_len(s + j, set);
		splitted[i] = malloc((len + 1) * sizeof(char));
		if (!(splitted[i]))
			return (free_arrays(splitted, i));
		ft_strlcpy(splitted[i], s + j, len + 1);
		j += len;
	}
	return (splitted);
}
