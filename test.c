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
		*rt = ft_strdup("$");
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
			ft_strlcpy(rt[j], &str[k], i - k + 1);
			j++;
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
			ft_strlcpy(rt[j], &str[k], i - k);
			j++;
		}
		else if (str[i] == '"')
		{
			i++;
			k = i;
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] && str[i] == '\"')
				i++;
			rt[j] = malloc(sizeof(char) * i - k + 1); 
			ft_strlcpy(rt[j], &str[k], i - k);
			j++;
		}
		else if (str[i] == '$')
		{
			i = dollar_case(str, &rt[j], i, msh);
			j++;
		}
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

	int i = 0;
	tokens = expansion("echo $PATH", &msh);
	printf("\n\n\n");
	while (tokens[i])
	{
		printf("tokens[%d] = '%s'\n", i, tokens[i]);
		i++;
	}
	free_array(tokens);
	exit_shell(&msh);
	// if (msh.exp != NULL)
	// {
	// 	free(msh.exp->data);
	// 	free(msh.exp);
	// }
	return (0);
}

//TODO : CHECK $ in double quotes

