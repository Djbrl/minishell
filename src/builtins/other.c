/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:21:15 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:02 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_env(t_env_var *env, t_msh *msh, char *field)
{
	t_env_var	*cur;
	int			len;

	(void)msh;
	(void)env;
	(void)field;
	cur = env;
	len = ft_strlen(cur->name);
	while (cur->next != NULL)
	{
		if (cur->name && cur->data && \
		ft_strncmp(cur->name, "init", len) != 0 && \
		ft_strncmp(cur->name, "?", len) != 0 && ft_strlen(cur->data) > 0)
			ft_putnstr(cur->name, "=", cur->data, "\n");
		cur = cur->next;
	}
	if (cur->name && cur->data && \
	ft_strncmp(cur->name, "init", len) != 0 && \
	ft_strncmp(cur->name, "?", len) && ft_strlen(cur->data) > 0)
		ft_putnstr(cur->name, "=", cur->data, "\n");
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}

int	msh_exit(t_env_var *env, t_msh *msh, char *field)
{
	int		exit_status;

	(void)env;
	if (!field)
		exit_status = exit_shell(msh, msh->prompt);
	else
		exit_status = exit_shell(msh, field);
	return (update_exit_status(msh, exit_status));
}

int	msh_pwd(t_env_var *env, t_msh *msh, char *field)
{
	char	cwd[1024];

	(void)field;
	(void)msh;
	(void)env;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf(PWD_ERR);
		update_exit_status(msh, 1);
	}
	else
		ft_putnstr(getcwd(cwd, sizeof(cwd)), "\n", NULL, NULL);
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}

int	msh_help(t_env_var *env, t_msh *msh, char *field)
{
	(void)field;
	(void)msh;
	(void)env;
	ft_putstr("\nminishell-4.2 commands: \n\necho\t\t: a clone of bash echo\n");
	ft_putstr("cd\t\t: a clone of bash cd\n");
	ft_putstr("pwd\t\t: a clone of bash pwd\n");
	ft_putstr("export\t\t: a clone of bash export\n");
	ft_putstr("env\t\t: a clone of bash env\n");
	ft_putstr("unset\t\t: a clone of bash unset\n");
	ft_putstr("help\t\t: show this list\n");
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}
