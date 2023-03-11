/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:15:31 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:26:41 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# include <string.h>
# include <errno.h>
# include <limits.h>

# define KGRN  "\x1B[32m"
# define KBLU  "\x1B[34m"
# define KCYN  "\x1B[36m"
# define KRED "\x1B[31m"
# define KRST "\x1B[0m"

# define SHELL_PID_ERROR "[SHELL_PID]"
# define SYNTAX_ERR_QUOTES "minishell: syntax error: invalid quotes or symbol\n"
# define PWD_ERR "pwd: getcwd: cannot access parent directories\n"
# define CHDIR_ERR "chdir: getcwd: cannot access parent directories\n"
# define CD_ARG_ERROR ": too many arguments\n"
# define ENV_ID_ERROR ": not a valid identifier\n"
# define FORK_ERROR ": couldn't start process\n"
# define PATH_ERROR ": No such file or directory\n"
# define CWD_ERROR ": couldn't retrieve current directory\n"
# define CMD_ERROR ": command not found\n"
# define HEREDOC_BUF_SIZE 1024
# define HEREDOC_LIMIT 100
# define MODE_DEFAULT 1
# define MODE_DIR 2
# define BUF 4096
# define RUNNING 1
# define PROMPTLINE "minishell-4.2$ > "
# define SUCCESS 0
# define FAILURE 127
# define STATUS_RESET 0
# define CTRL_C_EXIT 2
# define CTRL_D_SIGNAL -1
# define BUFFER_SIZE 4096

extern int				g_status;
typedef struct s_msh	t_msh;

typedef struct s_expr{
	char			*data;
	int				fd_in;
	int				fd_out;
	int				redir;
	struct s_expr	*next;
}					t_expr;

typedef struct s_env_var
{
	char				*name;
	char				*data;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_cmd
{
	int			(*ptr[8])(t_env_var*, t_msh *msh, char *field);
	char		*name[8];
}				t_cmd;

typedef struct s_msh
{
	t_cmd		cmd;
	t_expr		*exp;
	t_env_var	*env;
	char		*last_valid_path;
	char		*home;
	char		*user;
	char		*full_path;
	char		*default_path;
	char		*prompt;
	char		**tokens;
	char		**envp;
	char		**paths;
	char		g_buffer[BUF];
	int			nb_tokens;
	int			single_quote;
	int			exit_status;
	int			std_in;
	int			std_out;
}				t_msh;

/*
** INIT
*/
void		init_env(t_msh *msh);
void		init_msh(t_msh *msh, char **envp);
void		init_expr(t_msh *msh);

/*
** BUILTINS
*/
int			msh_cd(t_env_var *env, t_msh *msh, char *field);
int			msh_pwd(t_env_var *env, t_msh *msh, char *field);
int			msh_env(t_env_var *env, t_msh *msh, char *field);
int			msh_echo(t_env_var *env, char *s, t_msh *msh);
int			msh_help(t_env_var *env, t_msh *msh, char *field);
int			msh_exit(t_env_var *env, t_msh *msh, char *field);
int			msh_unset(t_env_var *env, t_msh *msh, char *field);
int			msh_export(t_env_var *env, char *arg, t_msh *msh);
int			msh_cd_runner(t_env_var *env, t_msh *msh, char *field);
int			msh_echo_runner(t_env_var *env, t_msh *msh, char *field);
int			msh_export_runner(t_env_var *env, t_msh *msh, char *field);

/*
** DISPLAY
*/
int			display_error(char *error, t_msh *msh);
void		display_prompt(int mode, t_msh *msh);
void		display_cmd_error(char *cmd, char *error, char **args);

/*
** CONTROL
*/
char		*get_currentdir(t_msh *msh);
char		*get_data_from_env(t_env_var *env, char *name);
void		free_data_from_env(t_env_var *env, char *name);
int			add_var_to_env(t_env_var *env, char *name, char *data);
void		evaluate_commands(t_msh *t_msh);
void		signal_handler(int sig_n);
void		read_buffer(t_msh *msh);
void		parse_envp(t_msh *msh);
void		exit_cmd(t_msh *msh);
int			exit_shell(t_msh *msh, char *field);

/*
** UTILS
*/
int			has_quote(char *str);
int			check_quotes(char **redir, int *i);
void		reload_path(t_msh *msh);
char		**remove_array_quotes(char **cmd);
void		copy_result(char **new_result, char **result, int len);
char		*remove_quotes(char *str);
void		close_main_fork_process(t_msh *msh, int pid);
int			is_redir(char *str);
int			expr_len(t_expr *expr);
int			load_expr(t_msh *msh);
void		free_expr(t_msh **msh);
char		*expand_var(t_msh *msh, char *var);
void		free_split(char **array);
int			get_next_line(int fd, char **line);
int			update_exit_status(t_msh *msh, int status);
int			is_builtin(char *s, t_msh *msh);
char		**ft_split_charset(const char *s, const char *set);
char		*remove_spaces(const char *str);
void		close_redir(int in, int out);
int			arr_len(char **arr);
void		free_envar(t_msh *msh);
void		free_env(t_msh *msh);
int			change_dir(t_msh **msh, char **tokens);
void		temp_exit(t_msh *msh);
char		**remove_array_quotes(char **cmd);
void		reload_path(t_msh *msh);
void		sort_env(t_env_var *env);
void		free_env_cpy(t_env_var *env);
void		build_promptline(char *user, char **promptline, t_msh *msh);
int			has_odd_quotes(char *str);
int			has_unexpected_token(char *str);
int			set_prompt(t_msh *msh);
int			has_quoted_spaces(char *str);
t_env_var	*env_duplicate(t_env_var *lst);

/*
** PIPE
*/

int			pipe_exec(t_msh *msh);
int			init_fds(t_expr **commands, t_expr *prev);
void		close_fds(t_expr **curr_command);
int			connect_fds(t_expr **curr_command, t_expr *commands);
void		exec_pipe_paths(t_msh *msh, char **re, char **cmd, char *field);
void		child_pipe(t_expr *curr, t_msh *msh);

/*
** REDIRECTIONS
*/
int			exec_builtin(t_msh *msh, char *field);
void		apply_redirections(char *expr, int *fd_in, int *fd_out, t_msh *msh);
int			check_redirections(t_msh *msh);
void		heredoc(char **field, t_msh *msh);
void		ftn_heredoc(char *cmd, char *buf[HEREDOC_LIMIT], t_msh *msh);
int			sneaky_redir(char *expr);
int			which_redir(char *redir, char *which, char dir, int mode);
int			is_redir_token(char *token, char **redirs);
int			is_sneaky_token(char *expr, int *i, int *fds[2], t_msh *msh);
void		heredoc_redirection(char **redirs, char **field, t_msh *msh);
void		input_redirection(char **f, int *fd_in, char *prompt, t_msh *msh);
void		output_redirection(char **field, int mode, int *fd_out);
int			handle_redir(char *expr, int *fds[2], int *i, t_msh *msh);
char		*heredoc_expand(char *tmp, t_msh *msh);

/*
** PARSING
*/
char		**parse_prompt(char *str, t_msh *msh);
void		add_to_rt(char **rt, char *tmp);
void		*ft_realloc(void *ptr, size_t cursize, size_t newsize);
int			is_pipe_redir(char c);
int			is_whitespace(char c);
int			dollar(char *str, char **rt, int i, t_msh *msh);
int			double_quote(char *str, char **rt, int i);
int			pipe_redir(char *str, char **rt, int i);
int			single_quote(char *str, char **rt, int i);
int			string(char *str, char **rt, int i);
int			pipe_redir_inside_quotes(char *str, char **rt, int i);
char		*expand_prompt(char *str, t_msh *msh);

#endif
