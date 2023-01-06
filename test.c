#include "include/minishell.h"

int	string(char *str, char **rt, int i, t_msh *msh);
int	single_quote(char *str, char **rt, int i, t_msh *msh);


char	*expand_env(char *str, t_msh *msh)
{
	int	i;
	char *tmp;
	char *rt;

	i = 0;
	rt = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i + 1);
	// printf("tmp = '%s'\n", tmp);
	// printf("$%s = '%s'\n", tmp, get_data_from_env(msh->env, tmp));
	rt = get_data_from_env(msh->env, tmp);
	free(tmp);
	return rt;
}

int	dollar_case(char *str, char **rt, int i, t_msh *msh)
{
	i++;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		*rt = ft_strdup(expand_env(&str[i], msh));
		while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	else
	{

		*rt = ft_strdup("$");
	}
	return (i);
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
		printf("1fois\n");
	}
	else
		*rt = ft_strdup(tmp);
}

int	dollar_case_inside_dquote(char *str, char **rt, int i, t_msh *msh)
{
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		replace_rt(rt, expand_env(&str[i], msh));
		while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	else
		replace_rt(rt, "$");
	return (i);
}

int	double_quote(char *str, char **rt, int i, t_msh *msh)
{
	int	k ;
	char *tmp;

	// tmp = ft_strdup("");
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
				i = dollar_case_inside_dquote(str, rt, i, msh);
				k = i;
			}
			else
				i++;
		}
		if (str[i] && str[i] == '\"')
			i++;
		// free(tmp);
		tmp = malloc(sizeof(char) * i - k + 1); 
		ft_strlcpy(tmp, &str[k], i - k);
		replace_rt(rt, tmp);
	}
	free(tmp);
	return i;
}

int	single_quote(char *str, char **rt, int i, t_msh *msh)
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

int	string(char *str, char **rt, int i, t_msh *msh)
{
	int k;
	char *tmp1;

	k = 0;
	if (str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '$')
	{
		k = i;
		while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != ' '))				
			i++;
		tmp1 = malloc(sizeof(char) * i - k + 1); 
		ft_strlcpy(tmp1, &str[k], i - k + 1);
	}
	replace_rt(rt, tmp1);
	free(tmp1);
	return (i);
}

int		check_which_case(char *str, char **rt, int i, t_msh *msh)
{
	while(str[i] && str[i] != ' ')
	{
		if (str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '$')
			i = string(str, rt, i, msh);
		else if (str[i] == '\'')
			i = single_quote(str, rt, i, msh);
		if (str[i] == '"')
			i = double_quote(str, rt, i, msh);
		else if (str[i] == '$')
			i = dollar_case(str, rt, i, msh);
		// i++;
	}
	return (i);
}

char	**expansion(char *str, t_msh *msh)
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
		while (str[i] && str[i] == ' ')
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
	char *prompt = "\"s\"\"a\"\"lut ca va\" \t bien ou 'k''o''i' echo \"BON$PATH\" \"l\"\'s\'sss \'sa\"lu\"t\' \"l\"\'s\'   ";
	// char *prompt = "\"1\"\"2\"bonjour ca va";
	// char *prompt = "\"BON$ PATH \"";
	// char *prompt = "echo $\"PATH\"";

	int i = 0;
	tokens = expansion(prompt, &msh);
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

//TODO : CHECK $ in double quotes + $"text"
//TODO : quand inside "" expand env
//TODO : "l"'s' -> quand fin quote (double et single) si juste apres char ou "" ou '' strjoin
//		 donc je pense int	double_quote(char *str, char **rt, int i, t_msh *msh + char *previous)


//TODO : check $ inside doublequotes
