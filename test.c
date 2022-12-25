#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char   *add_to_str(char *str, char c)
{
	char *rt;

	rt = malloc(strlen(str) + 2);
	rt = strcat(str, &c);

	return (rt);
}

int main(int ac, char *av[])
{
    char *first = "bonjour";
    char *str;
    int i = 0;

    // Allocate initial memory for str
    // str = malloc(1);
    // if (!str)
    // {
    //     // malloc failed, handle the error
    //     return 1;
    // }
    // str[0] = '\0';
	str = strdup("");
    if (ac > 1)
    {
        while (first[i])
        {
            str = add_to_str(str, first[i]);
    printf("str = %s\n", str);
            i++;
        }
    }


    // Free str when we're done using it
    free(str);

    return 0;
}


