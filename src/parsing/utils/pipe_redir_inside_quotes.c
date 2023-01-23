/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_inside_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:11:20 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/23 23:11:23 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redir_inside_quotes(char *str, char **rt, int i)
{
	char	*tmp;

	i++;
	tmp = malloc(sizeof(char) * (i + 2));
	ft_strlcpy(tmp, str, i + 1);
	tmp[i] = 6;
	tmp[i + 1] = '\0';
	add_to_rt(rt, tmp);
	free(tmp);
	return (i);
}
