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

	name = " $piwkomuszla$> ";
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
	char	*com;

	com = "pwd";

	print_intro();
	while (1)
	{
		line = _ft_readline();
		// if (!line)
		// 	printf("\n");
			
		ft_echo(line);
		if (!ft_strncmp(line, com, 3))
		{
			ft_pwd();
		}
		else
		{
			add_history(line);
//			get_tokens(line);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
