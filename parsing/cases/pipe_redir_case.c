/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_case.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:31:42 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/12 21:32:11 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redir_case(char *str, char **rt, int i, t_msh *msh)
{
	int		k;
	char	*tmp;

	k = i;
	while (str[i] && str[i] == str[k])
		i++;
	tmp = malloc(sizeof(char) * i - k + 1);
	ft_strlcpy(tmp, &str[k], i - k + 1);
	replace_rt(rt, tmp);
	free(tmp);
	return (i);
}
