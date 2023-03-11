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

int	has_quoted_spaces(char *str)
{
	int		i;
	int		has_space;

	i = 0;
	has_space = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			has_space = 1;
		i++;
	}
	return (has_space);
}

/*
****************************STATIC FUNCTIONS****************************
*/

// static int	var_name_len(char *name)
// {
// 	int	i;

// 	i = 0;
// 	while (name[i] != '$' && name[i])
// 		i++;
// 	return (i);
// }

// static void	ftn_msh_echo(char **var, char **arg, t_env_var **env, int i)
// {
// 	char		*t;
// 	char		*v;
// 	char		*a;
// 	t_env_var	*e;

// 	a = *arg;
// 	v = *var;
// 	e = *env;
// 	v = ft_substr(a, i + 1, var_name_len(a + i + 1));
// 	t = ft_strdup(get_data_from_env(e, v));
// 	if (t != NULL)
// 		ft_putstr(t);
// 	free(t);
// }

/*
****************************STATIC FUNCTIONS****************************
*/

/*
** MSH ECHO is ran by msh_echo_runner
*/
// static int	echo_dollar_check(char *arg, t_env_var *env, t_msh *msh)
// {
// 	// int		i;
// 	// char	*var;
// 	char	*tmp;
// 	char	*res;

// 	// i = 0;
// 	if (ft_strcmp(arg, "$") == 0)
// 		ft_putstr("$");
// 	else if (ft_strcmp(arg, "$$") == 0)
// 		ft_putstr(SHELL_PID_ERROR);
// 	else if (ft_strcmp(arg, "$?") == 0)
// 	{
// 		tmp = ft_strdup("?");
// 		res = ft_strdup(get_data_from_env(env, tmp));
// 		ft_putstr(res);
// 		free(res);
// 	}
// 	else
// 		ft_putstr(arg);
// 	(void)msh;
// 	// else if (arg[i] == '$' && ft_isalpha(arg[i + 1]) && !msh->single_quote)
// 	// 	ftn_msh_echo(&var, &arg, &env, i);
// 	return (0);
// }

// static void	more_than_one_word_exec(t_msh *msh, t_env_var *env)
// {
// 	int		i;
// 	int		j;
// 	char	**tmp;
// 	char	**args;

// 	j = 1;
// 	tmp = ft_split_charset(msh->prompt, "\"\'");
// 	if (tmp[1] == NULL)
// 	{
// 		args = ft_split(tmp[0], ' ');
// 		echo_dollar_check(args[1], env, msh);
// 		free_split(args);
// 		free_split(tmp);
// 		return ;
// 	}
// 	while (tmp[j])
// 	{
// 		args = ft_split(tmp[j], ' ');
// 		i = 0;
// 		while (args[i])
// 		{
// 			echo_dollar_check(args[i], env, msh);
// 			if (args[i + 1])
// 				write(1, " ", 1);
// 			i++;
// 		}
// 		free_split(args);
// 		i = 0;
// 		j++;
// 	}
// 	free_split(tmp);
// }

int	msh_echo(t_env_var *env, char *arg, t_msh *msh)
{
	(void)env;
	(void)msh;
	ft_putstr(arg);
	free(arg);
	return (0);
}
