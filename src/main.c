/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:56:56 by dsy               #+#    #+#             */
/*   Updated: 2020/12/07 17:01:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Partie obligatoire

Nom du programme : 
	- minishell

Fichiers de rendu :
	- Makefile, *.h, *.c
	- Makefile : NAME, all, clean, fclean, re

Arguments : Aucun

Fonctions externes autorisées
	-  readline, rl_clear_history, rl_on_new_line,
		rl_replace_line, rl_redisplay, add_history,
		printf, malloc, free, write, access, open, read,
		close, fork, wait, waitpid, wait3, wait4, signal,
		sigaction, sigemptyset, sigaddset, kill, exit,
		getcwd, chdir, stat, lstat, fstat, unlink, execve,
		dup, dup2, pipe, opendir, readdir, closedir,
		strerror, perror, isatty, ttyname, ttyslot, ioctl,
		getexpr, tcsetattr, tcgetattr, tgetent, tgetflag,
		tgetnum, tgetstr, tgoto, tputs
	-  Libft autorisée Oui

Description
	Votre shell doit :
	• Afficher un prompt en l’attente d’une nouvelle commande.
	• Posséder un historique fonctionnel.
	• Chercher et lancer le bon exécutable (en se basant sur 
		la variable d’exprironnement
	PATH, ou sur un chemin relatif ou absolu).
	• Ne pas utiliser plus d’une variable globale. 
		Réfléchissez-y car vous devrez justifier son utilisation.
	• Ne pas interpréter de quotes (guillemets) non fermés ou 
		de caractères spéciaux non
	demandés dans le sujet, tels que \ (le backslash) ou ; (le point-virgule).
	• Gérer ’ (single quote) qui doit empêcher le shell 
		d’interpréter les méta-caractères
	présents dans la séquence entre guillemets.
	• Gérer " (double quote) qui doit empêcher le shell 
		d’interpréter les méta-caractères
	présents dans la séquence entre guillemets sauf le $ (signe dollar).
	

	Minishell Aussi mignon qu’un vrai shell
	• Implémenter les redirections :
	◦ < doit rediriger l’entrée.
	◦ > doit rediriger la sortie.
	◦ << doit recevoir un délimiteur et lire l’input 
		donné jusqu’à rencontrer une ligne
	contenant le délimiteur. Cependant, l’historique 
		n’a pas à être mis à jour !
	◦ >> doit rediriger la sortie en mode append.
	• Implémenter les pipes (caractère |). La sortie de 
		chaque commande de la pipeline
	est connectée à l’entrée de la commande suivante grâce à un pipe.
	• Gérer les variables d’exprironnement (un $ suivi 
		d’une séquence de caractères)
	qui doivent être substituées par leur contenu.
	• Gérer $? qui doit être substitué par le statut de 
		sortie de la dernière pipeline
	exécutée au premier plan.
	• Gérer ctrl-C, ctrl-D et ctrl-\ qui doivent 
		fonctionner comme dans bash.
	• En mode interactif :
	◦ ctrl-C affiche un nouveau prompt sur une nouvelle ligne.
	◦ ctrl-D quitte le shell.
	◦ ctrl-\ ne fait rien.
	• Votre shell doit implémenter les builtins suivantes :
	◦ echo et l’option -n
	◦ cd uniquement avec un chemin relatif ou absolu
	◦ pwd sans aucune option
	◦ export sans aucune option
	◦ unset sans aucune option
	◦ expr sans aucune option ni argument
	◦ exit sans aucune option
	La fonction readline() peut causer des fuites de mémoire. 
		Vous n’avez pas à les
	gérer. Attention, cela ne veut pas pour autant dire que 
		votre code, oui celui que
	vous avez écrit, peut avoir des fuites de mémoire.
	Tenez-vous en à ce qui est demandé dans le sujet. Ce qui n’est pas
	demandé n’est pas obligatoire.
	Si vous avez un doute sur une consigne du sujet, prenez bash comme
	référence.
*/

/*
** MAIN FUNCTION
** -Display prompt : affiche le prompt 
** -Signal : definit la fonction a appeler lorsqu'on recoit 
**		un signal (CTRL+C, CTRL+D, CTRL+\)
** -Flush buffer : efface tout les caracteres(4096) present dans le buffer
**		en les remplacent par '0' avec ft_memset.
*/
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

static void	shell_loop(t_msh *msh)
{
	int	free_exp;

	free_exp = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	update_exit_status(msh, 0);
	while (RUNNING)
	{
		read_buffer(msh);
		msh->prompt = ft_strdup(msh->g_buffer);
		if (msh->prompt != NULL && ft_strlen(msh->prompt) != 0 \
			&& !only_whitespaces(msh->prompt))
		{
			free_exp = load_expr(msh);
			msh->tokens = ft_split(msh->prompt, ' ');
			msh->nb_tokens = get_nb_tokens(msh->tokens);
			evaluate_commands(msh);
			if (free_exp)
				free_split(msh->expr);
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
	shell_loop(&msh);
	return (0);
}
