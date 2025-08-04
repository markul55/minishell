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

char	*_ft_readline(void)
{
	char	*buffer;
	char	path[BUFSIZ];

	buffer = NULL;
	getcwd(path, sizeof(path));
	printf("%s$MiniShell$>", path);
	if (readline(buffer) == NULL)
	{
		buffer = NULL;
		printf("EOF");
	}
	return (buffer);
}

int main(void)
{
	char	*line;

	print_intro();
	while ((line = _ft_readline()) != NULL)
	{
		line = _ft_readline();
		printf("%s\n", line);
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
