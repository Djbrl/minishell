/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2023/01/28 03:15:19 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_arrays(char *arrays[HEREDOC_LIMIT])
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = NULL;
	while (arrays[i] != NULL)
	{
		if (result == NULL)
			result = ft_strdup(arrays[i]);
		else
		{
			tmp = ft_strjoin(result, " ");
			free(result);
			result = ft_strjoin(tmp, arrays[i]);
			free(tmp);
		}
		i++;
	}
	return (result);
}

static int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static void	expand_heredoc_var(char	*token, t_msh *msh, \
	char *heredoc_entry[HEREDOC_LIMIT], int *k)
{
	int		j;
	char	*var;
	char	*expand;

	j = 0;
	while (token[j])
	{
		if (token[j] == '$')
		{
			var = ft_strdup(get_data_from_env(msh->env, \
				ft_strdup(token + j + 1)));
			token[j] = '\0';
			expand = ft_strjoin(token, var);
			heredoc_entry[*k] = ft_strdup(expand);
			*k = *k + 1;
			free(var);
			free(expand);
		}
		j++;
	}
}

static char	*return_expand(char **tokens, \
	char *heredoc_entry[HEREDOC_LIMIT])
{
	int		i;
	char	*final;

	i = 0;
	final = concat_arrays(heredoc_entry);
	while (heredoc_entry[i])
		free(heredoc_entry[i++]);
	free_split(tokens);
	return (final);
}

char	*heredoc_expand(char *tmp, t_msh *msh)
{
	char	*heredoc_entry[HEREDOC_LIMIT];
	char	**tokens;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tokens = ft_split(tmp, ' ');
	while (k < HEREDOC_LIMIT)
		heredoc_entry[k++] = NULL;
	k = 0;
	while (tokens[i])
	{
		if (has_dollar(tokens[i]))
			expand_heredoc_var(tokens[i], msh, heredoc_entry, &k);
		else
		{
			heredoc_entry[k] = ft_strdup(tokens[i]);
			k++;
		}
		i++;
	}
	return (return_expand(tokens, heredoc_entry));
}
