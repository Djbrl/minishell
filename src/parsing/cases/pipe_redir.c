/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:35:02 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:35:04 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redir(char *str, char **rt, int i)
{
	int		k;
	char	*tmp;

	k = i;
	while (str[i] && str[i] == str[k])
		i++;
	tmp = malloc(sizeof(char) * i - k + 1);
	ft_strlcpy(tmp, &str[k], i - k + 1);
	add_to_rt(rt, tmp);
	if (tmp)
		free(tmp);
	return (i);
}
