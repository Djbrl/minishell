#include "include/minishell.h"

int	string_case(char *str, char **rt, int i, t_msh *msh);
int	single_quote_case(char *str, char **rt, int i, t_msh *msh);


int		is_whitespace(char c)
{
	if (c && ((c >= 9 && c <= 13) || c == 32))
		return (1);
	else
		return (0);
}

char	*expand_env(char *str, t_msh *msh)
{
	int	i;
	char *tmp;
	char *rt;

	i = 0;
	rt = NULL;
	while (str[i] && !is_whitespace(str[i]) && str[i] != '"' && str[i] != '\''
			&& str[i] != '|' && str[i] != '<' && str[i] != '>')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i + 1);
	rt = get_data_from_env(msh->env, tmp);
	free(tmp);
	return rt;
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	*str = 0;
	if (str)
		free(str);
}

void	free_n_array(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
}

void	replace_rt(char **rt, char *tmp)
{
	char *rt_cpy;

	if (*rt)
	{
		rt_cpy = ft_strdup(*rt);
		free(*rt);
		*rt = ft_strjoin(rt_cpy, tmp);
		free(rt_cpy);
	}
	else
		*rt = ft_strdup(tmp);
}

int	dollar_case(char *str, char **rt, int i, t_msh *msh)
{
	if (str[i] == '$')
		i++;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		replace_rt(rt, expand_env(&str[i], msh));
		while (str[i] && !is_whitespace(str[i]) && str[i] != '"' && str[i] != '\''
				&& str[i] != '|' && str[i] != '<' && str[i] != '>')
			i++;
	}
	else
		replace_rt(rt, "$");
	return (i);
}

int	double_quote_case(char *str, char **rt, int i, t_msh *msh)
{
	int	k ;
	char *tmp;

	if (str[i] == '\"' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && (str[i] != '\"'))
		{
			if (str[i] == '$')
			{
				i++;
				tmp = malloc(sizeof(char) * i - k + 1);
				ft_strlcpy(tmp, &str[k], i - k);
				replace_rt(rt, tmp);
				free(tmp);
				i = dollar_case(str, rt, i, msh);
				k = i;
			}
			else
				i++;
		}
		if (str[i] && str[i] == '\"')
			i++;
		tmp = malloc(sizeof(char) * i - k + 1); 
		ft_strlcpy(tmp, &str[k], i - k);
		replace_rt(rt, tmp);
	}
	free(tmp);
	return i;
}

int	single_quote_case(char *str, char **rt, int i, t_msh *msh)
{
	int	k ;
	char *tmp;

	tmp = ft_strdup("");
	if (str[i] == '\'' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] && str[i] == '\'')
			i++;
		free(tmp);
		tmp = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp, &str[k], i - k);
		replace_rt(rt, tmp);
	}
	free(tmp);
	return (i);
}

int	string_case(char *str, char **rt, int i, t_msh *msh)
{
	int k;
	char *tmp1;

	k = 0;
	if (str[i] != '\'' && str[i] != '"' && !is_whitespace(str[i]) && str[i] != '$'
		&& str[i] != '|' && str[i] != '<' && str[i] != '>')
	{
		k = i;
		while (str[i] && (str[i] != '\'' && str[i] != '"' && !is_whitespace(str[i]) &&
			str[i] != '$' && str[i] != '|' && str[i] != '<' && str[i] != '>'))				
			i++;
		tmp1 = malloc(sizeof(char) * i - k + 1); 
		ft_strlcpy(tmp1, &str[k], i - k + 1);
	}
	replace_rt(rt, tmp1);
	free(tmp1);
	return (i);
}

int		pipe_redir_case(char *str, char **rt, int i, t_msh *msh)
{
	int	k;
	char	*tmp;

	k = i;
	while (str[i] && str[i] == str[k])
		i++;
	tmp = malloc(sizeof(char) * i - k + 1); 
	ft_strlcpy(tmp, &str[k], i - k + 1);
	replace_rt(rt, tmp);
	free(tmp);
	return (i);
}

int		check_which_case(char *str, char **rt, int i, t_msh *msh)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')	// en dehors du while pr separer de ts les autres cas
		i = pipe_redir_case(str, rt, i, msh);
	else
		while(str[i] && !is_whitespace(str[i]) && str[i] != '|' && str[i] != '<'
			&& str[i] != '>')
		{
			if (str[i] != '\'' && str[i] != '"' && !is_whitespace(str[i]) && str[i] != '$')
				i = string_case(str, rt, i, msh);
			else if (str[i] == '\'')
				i = single_quote_case(str, rt, i, msh);
			else if (str[i] == '"')
				i = double_quote_case(str, rt, i, msh);
			else if (str[i] == '$')
				i = dollar_case(str, rt, i, msh);
		}
	return (i);
}

char	**parse_prompt(char *str, t_msh *msh)
{
	int	i;
	int	j;
	char	**rt;

	i = 0;
	j = 0;
	rt = ft_calloc(200, sizeof(rt));
	while (str[i])
	{
		i = check_which_case(str, &rt[j], i, msh);
		j++;
		while (str[i] && is_whitespace(str[i]))
			i++;
	}
	rt[j] = 0;
	return(rt);
}

int main(int ac, char *av[], char **envp)
{
	char **tokens;
	t_msh	msh;

	(void)ac;
	(void)av;
	init_env(&msh);
	init_msh(&msh, envp);
	char *prompt = "\"s\"\"a\"\"lut ca va\" \v bien ou 'k''o''i' |echo \"BON$PATH\" <>\"l\"\'s\'sss \'sa\"lu\"t\' \"l\"\'s\'  $\"PATH\" ";
	// char *prompt = "\"1\"\"2\"bonjour ca va";
	// char *prompt = "\"BON$ PATH \"";
	// char *prompt = "echo $\"PATH\"";
	// char *prompt = "a_$PATH";

	// char *prompt = "echo bonjour>rt || ls>><rt";

	// printf("is_pipe = %d\n", is_pipe(&pipe[1]));

	int i = 0;
	tokens = parse_prompt(prompt, &msh);
	printf("\n\nprompt = |%s|\n\n", prompt);
	while (tokens[i])
	{
		printf("tokens[%d] = '%s'\n", i, tokens[i]);
		i++;
	}
	printf("\n\n");
	free_array(tokens);
	exit_shell(&msh);
	// if (msh.exp != NULL)
	// {
	// 	free(msh.exp->data);
	// 	free(msh.exp);
	// }
	return (0);
}

//TODO : quand inside "" expand env
//TODO : "l"'s' -> quand fin quote (double et single) si juste apres char ou "" ou '' strjoin

//TODO : check dollar case : 	if (ft_isalpha(str[i]) || str[i] == '_')
