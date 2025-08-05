/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:14:00 by wkozlows          #+#    #+#             */
/*   Updated: 2025/08/04 01:14:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//Wyświetlanie ścieżki cwd i "$minishell$"
char	*generate_prompt(void)
{
	char	*prompt;
	char	path[BUFSIZ];
	char	*name;

	name = " $minishell$> ";
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	prompt = ft_strjoin(path, name);
	return (prompt);
}

//Rozbudowany readline(const char *prompt)
char	*_ft_readline(void)
{
	char	*buffer;
	char	*prompt;

	prompt = generate_prompt();
	if ((buffer = readline(prompt)) == NULL)
	{
		printf("EOF ");
	}
	free(prompt);
	return (buffer);
}

int main(void)
{
	char	*line;

	print_intro();
	while (1)
	{
		line = _ft_readline();
		if (!line)
		{
			printf("EXIT\n");
			break;
		if (*line)
			add_history(line);
		free(line);
		}

	}
	printf("\n");
	return (EXIT_SUCCESS);
}
