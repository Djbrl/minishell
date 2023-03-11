/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:13:26 by dsy               #+#    #+#             */
/*   Updated: 2023/01/16 16:37:46 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ****************************STATIC FUNCTIONS****************************
 * refactor these functions to read expri] properly
 */

static void	ftn_echo_runner(t_msh **msh, t_env_var **var, int i, char **tokens)
{
	i = 1;
	(void)msh;
	(void)var;
	while (tokens[i] != NULL)
	{
		if ((is_redir(tokens[i]) && ft_strlen(tokens[i]) < 3) \
			&& !has_quoted_spaces(tokens[i]))
			break ;
		if (tokens[i] != NULL)
		{
			if (has_quoted_spaces(tokens[i]))
				msh_echo(*var, ft_strdup(tokens[i]), *msh);
			else if (!ft_strcmp(tokens[i], "$"))
				write(1, "$", 1);
			else if (!ft_strcmp(tokens[i], "$$"))
				write(1, SHELL_PID_ERROR, ft_strlen(SHELL_PID_ERROR));
			else
				msh_echo(*var, remove_spaces(tokens[i]), *msh);
			if (tokens[i + 1] != NULL)
				write(1, " ", 1);
		}
		i++;
	}
}

static int	is_long_n(char *str)
{
	int	i;

	i = 1;
	if (ft_strlen(str) < 3)
		return (0);
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

static int	run_echo(t_msh **msh, t_env_var **env, char **tokens)
{
	int			i;
	int			exit;

	i = 0;
	exit = 0;
	while (tokens[++i])
	{		
		if (is_redir(tokens[i]) && ft_strlen(tokens[i]) < 3)
			break ;
		if (ft_strcmp(tokens[i], "-n") == 0)
			continue ;
		if (i != 1)
		{
			if (has_quoted_spaces(tokens[i]))
				exit = msh_echo(*env, ft_strdup(tokens[i]), *msh);
			else
				exit = msh_echo(*env, remove_spaces(tokens[i]), *msh);
		}
		if (tokens[i + 1] != NULL && i != 1)
			write(1, " ", 1);
	}
	return (exit);
}

static void	check_options(t_msh *msh, t_env_var *env, char **tokens)
{
	int	i;

	i = 1;
	if (!tokens[1])
		write(1, "\n", 1);
	else if (ft_strncmp(tokens[1], "-n", ft_strlen(tokens[1])) == 0 || \
	is_long_n(tokens[1]))
		run_echo(&msh, &env, tokens);
	else
	{
		ftn_echo_runner(&msh, &env, i, tokens);
		write(1, "\n", 1);
	}
	exit_cmd(msh);
}

/*
****************************STATIC FUNCTIONS****************************
*/

int	msh_echo_runner(t_env_var *env, t_msh *msh, char *field)
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
	check_options(msh, env, tokens);
	if (free_tokens)
		free_split(tokens);
	return (update_exit_status(msh, exit_status));
}
