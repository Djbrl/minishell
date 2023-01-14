/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_expand_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:17:24 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:53 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The 'ft_strlen() + 1' is meant to check if there 
** are any extra characters after the builtin name string
*/
int	is_builtin(char *s, t_msh *msh)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(msh->cmd.name[i], s, ft_strlen(msh->cmd.name[i]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_var(t_msh *msh, char *var)
{
	char	*ret;
	char	*find;

	find = ft_substr(var, 1, ft_strlen(var) - 1);
	ret = get_data_from_env(msh->env, find);
	if (ret == NULL)
		return (ft_strdup(var));
	else
		return (ft_strdup(ret));
}

void	flush_buffer(t_msh *msh)
{
	ft_memset(msh->g_buffer, 0, BUF);
}

void	read_buffer(t_msh *msh)
{
	int	signal;

	flush_buffer(msh);
	if (g_status == CTRL_C_EXIT)
		g_status = STATUS_RESET;
	else
		display_prompt(MODE_DEFAULT, msh);
	signal = read(0, msh->g_buffer, BUF);
	if (signal == CTRL_D_SIGNAL)
	{
		flush_buffer(msh);
		exit_cmd(msh);
		exit_shell(msh);
	}
	msh->g_buffer[ft_strlen(msh->g_buffer) - 1] = 0;
}

// void	read_buffer(t_msh *msh)
// {
// 	// int	signal;
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = readline(PROMPTLINE);
// 	if (s != NULL)
// 	{
// 		add_history(s);
// 		if (ft_strlen(s) == 0)
// 		{
// 		//	write(1, "\n", 1);
// 			return ;
// 		}
// 		else
// 		{
// 			while (s[i] && s[i] != '\n')
// 			{
// 				msh->g_buffer[i] = s[i];
// 				i++;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		flush_buffer(msh);
// 		exit_cmd(msh);
// 		exit_shell(SUCCESS, msh);
// 		return ;
// 	}
// 	free(s);
// }
