/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:35:25 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:35:27 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string(char *str, char **rt, int i)
{
	int		k;
	char	*tmp;

	k = 0;
	if (str[i] != '\'' && str[i] != '"' && !is_whitespace(str[i])
		&& !is_pipe_redir(str[i]))
	{
		k = i;
		while (str[i] && (str[i] != '\'' && str[i] != '"'
				&& !is_whitespace(str[i]) && !is_pipe_redir(str[i])))
			i++;
		tmp = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp, &str[k], i - k + 1);
		add_to_rt(rt, tmp);
		free(tmp);
	}
	return (i);
}
