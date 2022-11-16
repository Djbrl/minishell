/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:03:55 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/11/15 01:03:58 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_nb_quotes(char *str)
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
		if (str[i] == '\"')
			double_quote++;
		i++;		
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	correct_quoting(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_quote(char *str)
{
	int	i;

	i = 0;
	if (check_nb_quotes(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (str[i])
	{
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char *av[])
{
	if (ac > 1)
		printf("%d\n", check_nb_quotes(av[1]));
	return (0);
}
