/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:14:00 by wkozlows          #+#    #+#             */
/*   Updated: 2025/09/14 12:00:00 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prompt: "<cwd> $piwkomuszla$> " */
char    *generate_prompt(void)
{
    char    *prompt;
    char    path[PATH_MAX];
    const char *name = " $piwkomuszla$> ";

    if (getcwd(path, sizeof(path)) == NULL)
    {
        perror("getcwd");
        return ft_strdup("$> ");
    }
    prompt = ft_strjoin(path, name);
    return prompt;
}

/* readline wrapper */
char    *_ft_readline(void)
{
    char    *buffer;
    char    *prompt = generate_prompt();

    buffer = readline(prompt);
    free(prompt);
    return buffer;
}

/* Simple dispatcher for a single command without pipes/redirs */
static int handle_simple_command(t_list *tokens)
{
    char **argv = tokens_to_argv_words(tokens);
    int status = 0;

    if (!argv || !argv[0])
    {
        free_argv(argv);
        return 0;
    }

    if (ft_strncmp(argv[0], "pwd", 3) == 0 && ft_strlen(argv[0]) == 3)
        cmd_pwd();
    else if (ft_strncmp(argv[0], "echo", 4) == 0 && ft_strlen(argv[0]) == 4)
        status = cmd_echo(argv);
    else if (ft_strncmp(argv[0], "exit", 4) == 0 && ft_strlen(argv[0]) == 4)
        cmd_exit();
    else
        fprintf(stderr, "minishell: external commands not implemented yet\n");

    free_argv(argv);
    return status;
}

int main(void)
{
    char    *line;

    print_intro();
    while (1)
    {
        line = _ft_readline();
        if (!line) /* Ctrl-D */
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);

        t_list *tokens = tokenize(line);
        if (!tokens) { free(line); continue; }

        /* Detect operators for now and warn (future work) */
        bool has_op = false;
        for (t_list *cur = tokens; cur; cur = cur->next)
        {
            t_token *t = (t_token*)cur->content;
            if (t && t->type != T_WORD) { has_op = true; break; }
        }
        if (has_op)
            fprintf(stderr, "minishell: pipes/redirs not implemented yet (coming soon)\n");
        else
            handle_simple_command(tokens);

        ft_lstclear(&tokens, token_free);
        free(line);
    }
    return (EXIT_SUCCESS);
}
