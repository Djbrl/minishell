#include "minishell.h"

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

int	main(int ac, char *av[], char **envp)
{
	char	**tokens;
	t_msh	msh;

	(void)ac;
	(void)av;
	init_env(&msh);
	init_msh(&msh, envp);
	char *prompt = "\"s\"\"a\"\"\101lut ca va\" \v bien ou 'k''o''i' |echo \"BON$PATH\" <>\"l\"\'s\'sss \'sa\"lu\"t\' \"l\"\'s\'  $\"PATH\" \"redir >> dquotes\" \'pipe | squote\'";
	// char *prompt = "\"1\"\"2\"bonjour ca va";
	// char *prompt = "\"BON$ PATH \"";
	// char *prompt = "echo $\"PATH\"";
	// char *prompt = " saltu \'bonjour";
	// char *prompt = "\"l\"s";
	// char *prompt = "echo bonjour>rt || ls>><rt";
	// char *prompt = NULL;
	// char *prompt = "\"ls > rt\"";

	int i = 0;
	tokens = parse_prompt(prompt, &msh);
	printf("\n\nPrompt = [%s]\n\n", prompt);
	while (tokens && tokens[i])
	{
		printf("tokens[%d] = '%s'\n", i, tokens[i]);
		i++;
	}
	printf("\n\n");
	if (tokens)
		free_array(tokens);
	exit_shell(&msh);
	return (0);
}

//TODO : check les var d'env si alphanum _ ...
//TODO : check dollar case : 	if (ft_isalpha(str[i]) || str[i] == '_')


// gcc -g3 -Iinclude libft/*.c main_parse_prompt.c parsing/parse_prompt.c parsing/utils/*.c parsing/cases/*.c src/*.c src/builtins/*.c src/pipex/*.c src/utils/*.c  && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./a.out