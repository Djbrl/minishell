/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:32 by dsy               #+#    #+#             */
/*   Updated: 2023/01/26 14:16:26 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ftn_exit(t_msh *msh, int status, char **arr)
{
	exit_cmd(msh);
	close(msh->std_in);
	close(msh->std_out);
	free_env(msh);
	if (msh->exp != NULL)
	{
		free(msh->exp->data);
		free(msh->exp);
	}
	if (arr != NULL)
		free_split(arr);
	clear_history();
	exit(status);
}

void	free_envar(t_msh *msh)
{
	if (msh->home != NULL)
		free(msh->home);
	if (msh->user != NULL)
		free(msh->user);
	if (msh->full_path != NULL)
		free(msh->full_path);
	if (msh->default_path != NULL)
		free(msh->default_path);
	if (msh->paths != NULL)
		free_split(msh->paths);
}

void	free_env(t_msh *msh)
{
	t_env_var	*cur;

	if (!msh->env)
		return ;
	while (msh->env->next != NULL)
	{
		cur = msh->env;
		free(msh->env->data);
		free(msh->env->name);
		msh->env = msh->env->next;
		free(cur);
	}
	if (msh->env)
	{
		free(msh->env->data);
		free(msh->env->name);
		free(msh->env);
	}
	free_envar(msh);
}

static int	check_exit_token(char *token)
{
	if ((token && ft_atoi(token) == 0 && \
		ft_strncmp(token, "0", ft_strlen(token)) != 0) \
		|| !ft_isnum(token) || (ft_isnum(token) && ft_strlen(token) > 9))
		return (1);
	return (0);
}

int	exit_shell(t_msh *msh, char *field)
{
	char	**arr;
	int		exit_status;

	exit_status = msh->exit_status;
	if (ft_strcmp(field, "exit") == 0)
		ftn_exit(msh, exit_status, NULL);
	arr = ft_split(field, ' ');
	if (check_exit_token(arr[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ftn_exit(msh, 2, arr);
	}
	if (arr_len(arr) == 2 && ft_isnum(arr[1]))
		exit_status = ft_atoi(arr[1]);
	if (arr_len(arr) > 2 && ft_isnum(arr[1]))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_split(arr);
		return (1);
	}
	free_split(arr);
	ftn_exit(msh, exit_status, NULL);
	return (0);
}
