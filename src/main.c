/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:56:56 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:37 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

static int	get_nb_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i] != NULL)
		i++;
	return (i);
}

static void	clean_expr(t_msh *msh, int free_flag)
{
	if (free_flag)
	{
		free_expr(&msh);
		init_expr(msh);
	}
	return ;
}

static void	launch_command(t_msh *msh)
{
	int	free_exp;

	free_exp = load_expr(msh);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (msh->nb_tokens > 0)
		evaluate_commands(msh);
	clean_expr(msh, free_exp);
	exit_cmd(msh);
	ft_memset(msh->g_buffer, 0, BUF);
}

static void	shell_loop(t_msh *msh)
{
	update_exit_status(msh, 0);
	while (RUNNING)
	{
		if (set_prompt(msh))
		{
			msh->tokens = parse_prompt(msh->prompt, msh);
			msh->nb_tokens = get_nb_tokens(msh->tokens);
			launch_command(msh);
		}
		else
			free(msh->prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	init_env(&msh);
	init_msh(&msh, envp);
	init_expr(&msh);
	shell_loop(&msh);
	return (0);
}
