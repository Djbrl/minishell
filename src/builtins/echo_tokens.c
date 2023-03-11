/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <dsy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:19:12 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:27:22 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_token(t_msh **msh, t_env_var **env, char *token)
{
	t_env_var	*e;
	t_msh		*m;
	int			exit;

	exit = 0;
	m = *msh;
	e = *env;
	if (has_quoted_spaces(tokens))
		exit = msh_echo(e, ft_strdup(token), m);
	else
		exit = msh_echo(e, remove_spaces(token), m);
	return (exit);
}

static int	handle_tokens(t_msh **msh, t_env_var **env, char **tokens, int *i)
{
	int		exit;

	exit = 0;
	while (tokens[*i])
	{
		if (is_redir(tokens[*i]))
			break ;
		if (ft_strcmp(tokens[*i], "-n") == 0)
		{
			(*i)++;
			continue ;
		}
		if (*i != 1)
		{
			exit = handle_token(msh, env, tokens[*i]);
			if (tokens[*i + 1] != NULL && *i != 1)
				write(1, " ", 1);
		}
		(*i)++;
	}
	return (exit);
}

int	run_echo(t_msh **msh, t_env_var **env, char **tokens)
{
	int	i;
	int	exit;

	i = 1;
	exit = handle_tokens(msh, env, tokens, &i);
	return (exit);
}
