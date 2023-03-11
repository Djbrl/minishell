/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_expand_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:17:24 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:53 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** The 'ft_strlen() + 1' is meant to check if there 
 ** are any extra characters after the builtin name string
 */
static int	has_odd_quotes(char *str)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			quotes++;
		i++;
	}
	return (quotes % 2 == 1);
}

char	*get_input_from_user(char *promptline)
{
	char	*s;

	s = readline(promptline);
	free(promptline);
	return (s);
}

int	check_input_validity(char *s)
{
	if (s == NULL)
		return (0);
	if (has_odd_quotes(s))
	{
		printf(SYNTAX_ERR_QUOTES);
		return (0);
	}
	if (has_unexpected_token(s))
	{
		printf(SYNTAX_ERR_QUOTES);
		return (0);
	}
	return (1);
}

void	process_input(t_msh *msh, char *s)
{
	int		i;

	if (ft_strlen(s) == 0)
		ft_memset(msh->g_buffer, 0, BUF);
	else
	{
		i = -1;
		while (s[++i] && s[i] != '\n')
			msh->g_buffer[i] = s[i];
	}
	free(s);
}
