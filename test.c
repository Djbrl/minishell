#include "include/minishell.h"

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

char	**expansion(char *str)
{
	int	i = 0;
	int	j = 0;
	char	**rt;

	rt = ft_calloc(200, sizeof(rt));
	while (str[i])
	{
		int k = 0;
		if (str[i] != '\'' && str[i] != '"' && str[i] != ' ')
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
		else if (str[i] && str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	rt[j] = 0;
	return(rt);
}

int main(int ac, char *av[])
{
		char **tokens;

		int i = 0;
		tokens = expansion("mot_seul \"unephrase entiere\" \'entre quotes simples\'");

		while (tokens[i])
		{
			printf("tokens[%d] = '%s'\n", i, tokens[i]);
			i++;
		}
		free_array(tokens);
	return (0);
}

