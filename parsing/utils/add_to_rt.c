/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:44:08 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:44:10 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_rt(char **rt, char *tmp)
{
	char	*rt_cpy;

	if (*rt)
	{
		rt_cpy = ft_strdup(*rt);
		free(*rt);
		*rt = ft_strjoin(rt_cpy, tmp);
		free(rt_cpy);
	}
	else
		*rt = ft_strdup(tmp);
}
