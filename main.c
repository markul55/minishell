#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(int ac, char **av)
{
	if (ac == 2)
	{
	char *input;

    input = readline("Wpisz coś: ");

	if (input = "echo")
	{
		printf("%s\n", av[1]);
	}
	}
	printf("\n");
	return(0);
}
