/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:18:10 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/02/25 00:18:14 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	doll_to_expand(char *str, int i)
{
	int	j;
	int	squote_nb;
	int	dquote_nb;

	j = 0;
	squote_nb = 0;
	dquote_nb = 0;
	if (str[i] && str[i] == '$')
	{
		while (j < i)
		{
			if (str[j] == '\'')
				squote_nb++;
			if (str[j] == '"' && squote_nb % 2 == 0)
				dquote_nb++;
			j++;
		}
		if (squote_nb % 2 == 0 || (squote_nb % 2 == 1 && dquote_nb % 2 == 1))
			return (1);
	}
	return (0);
}

static int	not_dollar(char *str, char **rt, int i)
{
	int		start;
	char	*tmp;

	start = i;
	while (str[i] && !doll_to_expand(str, i))
		i++;
	if (i > start)
	{
		tmp = malloc(sizeof(char) * i - start + 1);
		ft_strlcpy(tmp, &str[start], i - start + 1);
		add_to_rt(rt, tmp);
		free(tmp);
	}
	return (i);
}

char	*expand_prompt(char *str, t_msh *msh)
{
	int		i;
	char	*rt;

	i = 0;
	rt = ft_strdup("");
	while (str && str[i])
	{
		if (doll_to_expand(str, i))
			i = dollar(str, &rt, i, msh);
		else
			i = not_dollar(str, &rt, i);
	}
	return (rt);
}
