#include "include/minishell.h"

char	*expand_env(char *str, t_msh *msh)
{
	int	i;
	char *tmp;
	char *rt;

	i = 0;
	rt = NULL;
	while (str[i] && str[i] != ' ')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i + 1);
	printf("tmp = '%s'\n", tmp);
	printf("$%s = '%s'\n", tmp, get_data_from_env(msh->env, tmp));
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
		while (str[i] && str[i] != ' ')
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

int	double_quote(char *str, char **rt, int i, t_msh *msh)
{
	int	k ;
	char *tmp[2];

	tmp[0] = ft_strdup("");
	tmp[1] = ft_strdup("");
	*rt = ft_strdup("");
	while (str[i] == '\"' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] && str[i] == '\"')
			i++;
		free(tmp[0]);
		tmp[0] = malloc(sizeof(char) * i - k + 1); 
		ft_strlcpy(tmp[0], &str[k], i - k);
		free(tmp[1]);
		tmp[1] = ft_strjoin(*rt, tmp[0]);
		free(*rt);
		*rt = ft_strdup(tmp[1]);
	}
	free(tmp[0]);
	free(tmp[1]);
	return i;
}



char	**expansion(char *str, t_msh *msh)
{
	int	i = 0;
	int	j = 0;
	char	**rt;
	char	*tmp;

	rt = ft_calloc(200, sizeof(rt));
	while (str[i])
	{
		int k = 0;
		tmp = NULL;
		if (str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '$')
		{
			k = i;
			while (str[i] && (str[i] != '\'' && str[i] != '"' && str[i] != ' '))				
				i++;
			rt[j] = malloc(sizeof(char) * i - k + 1); 
			ft_strlcpy(rt[j++], &str[k], i - k + 1);
			// j++;
		}
		else if (str[i] == '\'')
		{
			i++;
			k = i;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] && str[i] == '\'')
				i++;
			rt[j] = malloc(sizeof(char) * i - k + 1); 
			ft_strlcpy(rt[j++], &str[k], i - k);
			// j++;
		}
		else if (str[i] == '"')
			i = double_quote(str, &rt[j++], i, msh);
		else if (str[i] == '$')
			i = dollar_case(str, &rt[j++], i, msh);
		else if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
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
	char *prompt = "\"salut ca va\" bien ou 'koi'";
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

