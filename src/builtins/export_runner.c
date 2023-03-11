/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_runner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:13:26 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:27:45 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
*/

static int	is_env_var(t_env_var *e)
{
	if (e->name && e->data && \
		ft_strncmp(e->name, "init", ft_strlen(e->name)) != 0 && \
		ft_strncmp(e->name, "?", ft_strlen(e->name)))
		return (1);
	return (0);
}

static int	list_exports(t_env_var *env, t_msh *msh)
{
	t_env_var	*e;
	t_env_var	*e_head;

	e = env_duplicate(env);
	e_head = e;
	sort_env(e);
	while (e->next != NULL)
	{
		if (is_env_var(e))
		{
			write(1, "export ", 7);
			ft_putnstr(e->name, "=", e->data, "\n");
		}
		e = e->next;
	}
	if (is_env_var(e))
	{
		write(1, "export ", 7);
		ft_putnstr(e->name, "=", e->data, "\n");
	}
	free_env_cpy(e_head);
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}

static int	ftn_msh_export(t_msh *msh, char **tokens, t_env_var **envar)
{
	int			exit_status;
	int			i;
	t_env_var	*env;

	i = 1;
	env = *envar;
	exit_status = 0;
	if (tokens[1] == NULL)
	{
		list_exports(env, msh);
		exit_cmd(msh);
		return (update_exit_status(msh, 0));
	}
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
			break ;
		exit_status = msh_export(env, tokens[i], msh);
		i++;
	}
	exit_cmd(msh);
	return (exit_status);
}

/*
****************************STATIC FUNCTIONS****************************
*/

int	msh_export_runner(t_env_var *env, t_msh *msh, char *field)
{
	int		exit_status;
	int		free_tokens;
	char	**tokens;

	free_tokens = 0;
	exit_status = 0;
	if (field == NULL)
		tokens = msh->tokens;
	else
	{
		tokens = ft_split(field, ' ');
		free_tokens = 1;
	}
	exit_status = ftn_msh_export(msh, tokens, &env);
	if (free_tokens)
		free_split(tokens);
	return (update_exit_status(msh, exit_status));
}
