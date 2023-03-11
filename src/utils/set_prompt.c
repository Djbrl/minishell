/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 02:10:51 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:39 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_whitespaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && \
			buf[i] != '\v' && buf[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	set_prompt(t_msh *msh)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	read_buffer(msh);
	msh->prompt = ft_strdup(msh->g_buffer);
	if (msh->prompt != NULL && ft_strlen(msh->prompt) != 0 \
			&& !only_whitespaces(msh->prompt))
		return (1);
	return (0);
}
