/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:26:08 by dsy               #+#    #+#             */
/*   Updated: 2022/10/14 18:26:39 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_exit_status(t_msh *msh, int status)
{
	char	*tmp;

	tmp = ft_itoa(status);
	add_var_to_env(msh->env, "?", tmp);
	free(tmp);
	return (status);
}
