/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:28:47 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/11/27 17:28:51 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_quote(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote++;
		else if (str[i] == '\"')
			double_quote++;
		if (str[i] == '\'' || str[i] == '\"')
			i = inside_quote(str, i, str[i]);
		else
			i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
