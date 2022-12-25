#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char   *add_to_str(char *str, char c)
{
	char *rt;
	char *sec;

	rt = malloc(sizeof(rt) * (strlen(str) + 1) + 1);
	rt = strcat(str, &c);

	return (rt);
}