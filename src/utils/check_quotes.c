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

void	free_str(char *str)
{
	int i = 0;

	while (str[i])
	{
		free(str[i]);
	}
}

char	*add_char_to_str(char *str, char c)
{
	char *rt;
	char char_to_add[2];
	int size;

	size = ft_strlen(str) + 2;
	char_to_add[0] = c;
	char_to_add[1] = '\0';
	rt = ft_strjoin(str, char_to_add);
	return (rt);
}

int	check_quotes(char *str)
{
	int	i;
	int inside_str_quotes;
	int	single_quote;
	int	double_quote;
	char *final_string;
	char *tmp;


	i = 0;
	single_quote = 0;
	double_quote = 0;
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
		while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != ' ' ))
		{
			
		}
		// inside_str_quotes = -1;
		// if (str[i] == '\'')
		// {
		// 	single_quote++;
		// 	inside_str_quotes = i;
		// }
		// else if (str[i] == '\"')
		// {
		// 	double_quote++;
		// 	inside_str_quotes = i;
		// }
		// if (str[i] == '\'' || str[i] == '\"')
		// 	i = inside_quote(str, i, str[i]);
		// else
		// {
		// 	tmp = add_char_to_str(final_string, str[i]);
		// 	i++;
		// }
		// final_string = tmp;
		// if (tmp)
		// 	free(tmp);
	}
	printf("final str = %s\n", final_string);
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
		return (EXIT_FAILURE);
	expand_quotes(str);
	free(final_string);
	
	return (EXIT_SUCCESS);
}
