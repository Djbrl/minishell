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
	while (tokens[i] != NULL)
		i++;
	return (i);
}

static int	only_whitespaces(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && \
			buf[i] != '\v' && buf[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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

static void	shell_loop(t_msh *msh)
{
	int	free_exp;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	update_exit_status(msh, 0);
	while (RUNNING)
	{
		free_exp = 0;
		read_buffer(msh);
		msh->prompt = ft_strdup(msh->g_buffer);
		if (msh->prompt != NULL && ft_strlen(msh->prompt) != 0 \
			&& !only_whitespaces(msh->prompt))
		{
			free_exp = load_expr(msh);
			msh->tokens = parse_prompt(msh->prompt, msh);
			msh->nb_tokens = get_nb_tokens(msh->tokens);
			evaluate_commands(msh);
			clean_expr(msh, free_exp);
			exit_cmd(msh);
			flush_buffer(msh);
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
