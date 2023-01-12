/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:36:30 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/12 21:36:33 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_case(char *str, char **rt, int i, t_msh *msh)
{
	int		k;
	char	*tmp1;

	k = 0;
	if (str[i] != '\'' && str[i] != '"' && !is_whitespace(str[i])
		&& str[i] != '$' && !is_pipe_redir(str[i]))
	{
		k = i;
		while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != '$'
				&& !is_whitespace(str[i]) && !is_pipe_redir(str[i])))
			i++;
		tmp1 = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp1, &str[k], i - k + 1);
	}
	replace_rt(rt, tmp1);
	free(tmp1);
	return (i);
}
