/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:59:57 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:24 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_error(char *error, t_msh *msh)
{
	if (!ft_strncmp(error, CWD_ERROR, ft_strlen(error)))
		ft_putnstr("minishell: ", error, NULL, NULL);
	else if (!(ft_strncmp(error, CMD_ERROR, ft_strlen(error))))
		ft_putnstr("minishell: ", msh->tokens[0], CMD_ERROR, NULL);
	else if (!(ft_strncmp(error, FORK_ERROR, ft_strlen(error))))
		ft_putnstr("minishell: ", error, NULL, NULL);
	else if (!(ft_strncmp(error, ENV_ID_ERROR, ft_strlen(error))))
		ft_putnstr("minishell: ", "export", NULL, error);
	else if (!(ft_strncmp(error, CD_ARG_ERROR, ft_strlen(error))))
		ft_putnstr("minishell: ", "cd", error, NULL);
	else
		ft_putnstr("minishell: ", "unknown error\n", error, NULL);
	return (0);
}

void	display_cmd_error(char *cmd, char *error, char **args)
{
	if (!ft_strncmp(error, PATH_ERROR, ft_strlen(error)))
	{
		ft_putnstr("minishell: ", cmd, ": ", args[1]);
		ft_putstr(error);
	}
}

void	display_prompt(int mode, t_msh *msh)
{
	char	*path;

	if (mode == MODE_DIR)
	{
		path = get_currentdir(msh);
		ft_putnstr(path, "$ > ", NULL, NULL);
		free(path);
	}
	else
		ft_putstr(PROMPTLINE);
}
