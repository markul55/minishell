/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:06:13 by wkozlows          #+#    #+#             */
/*   Updated: 2025/09/14 17:38:32 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <ctype.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

/* === libft === */
# include "libft/libft.h"   /* wymagane: t_list, ft_* funkcje */

/* === Token types === */
typedef enum e_token_type
{
    T_WORD,       /* słowo / argument */
    T_PIPE,       /* | */
    T_REDIR_IN,   /* < */
    T_REDIR_OUT,  /* > */
    T_APPEND,     /* >> */
    T_HEREDOC     /* << */
}   t_token_type;

/* === Token === */
typedef struct s_token
{
    t_token_type type;
    char         *value; /* dla operatorów to np. ">>", "<", itp. */
}   t_token;

/* === ASCII art intro === */
void    print_intro(void);

/* === Readline helpers === */
char    *generate_prompt(void);
char    *_ft_readline(void);

/* === Builtins === */
void    cmd_pwd(void);
int     cmd_echo(char **argv);
int     cmd_exit(void);

/* === Utils: whitespace === */
int     skip_spaces(const char *text, int i);

/* === Tokens / Lexer === */
t_token *token_new(t_token_type type, const char *value);
void    token_free(void *tokptr);
t_list  *tokenize(const char *line); /* lista t_token* */

/* === Helpers to build argv from tokens (simple command only) === */
char  **tokens_to_argv_words(t_list *tokens);
void    free_argv(char **argv);

/* === External commands === */
char *find_executable(const char *cmd);
int   run_external(char **argv);
int ft_isspace(int c);

#endif
