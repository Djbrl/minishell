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

static int	inside_quote(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	expand_quotes(char *str)
{
	(void) str;
	// int	i;
	// int	start;
	// int	len;
	// char	*str_current;
	// char	*str_add;

	// i = 0;
	// str_current = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '\"')
	// 	{
	// 		i++;
	// 		if (str[i])
	// 		{
	// 			start = i;
	// 			len = 0;
	// 			while (str[i++] != '\"')
	// 				len++;
	// 			str_add = ft_substr(str, start, len);
	// 			printf("%s\n", str_add);
	// 		}
	// 	}
	// 	else
	// 	{
	// 		start = i;
	// 		len = 0;
	// 		while (str[i] && str[i] != '\"')
	// 		{
	// 			i++;
	// 			len++;
	// 		}
	// 		str_add = ft_substr(str, start, len);
	// 	}
	// }
	// printf("%s\n", str_current);
}

char	*add_to_str(char *str, char c)
{
	char *rt;

	rt = malloc(sizeof(rt) * (strlen(str) + 1));
	strcat(str, &c);

	return (rt);
}

int	check_quotes(char *str)
{
	int	i;
	int inside_str_quotes;
	int	single_quote;
	int	double_quote;
	char *final_string;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	// final_string = NULL;
	final_string = ft_strdup("");
	// char **split = ft_split_str(str, "\'\"");
	// strcpy(final_string, "");
	// while (split[i])
	// {
	// 	printf("%d - '%s'\n", i, split[i]);
	// 	i++;
	// }
	i = 0;
	while (str[i])
	{
			printf("0final str = %s\n", final_string);
		inside_str_quotes = -1;
		if (str[i] == '\'')
		{
			single_quote++;
			inside_str_quotes = i;
		}
		else if (str[i] == '\"')
		{
			double_quote++;
			inside_str_quotes = i;
		}
		if (str[i] == '\'' || str[i] == '\"')
			i = inside_quote(str, i, str[i]);
		else
		{
			final_string = add_to_str(final_string, str[i]);
			printf("final str = %s\n", final_string);
			// printf("final str = %s\n", final_string);
			// final_string = strcat(final_string, &str[i]);
			i++;
		}

	}

	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (EXIT_FAILURE);
	expand_quotes(str);
	return (EXIT_SUCCESS);
}
