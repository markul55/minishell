#include "minishell.h"

/* Create and free tokens */
t_token *token_new(t_token_type type, const char *value)
{
    t_token *t = (t_token*)malloc(sizeof(t_token));
    if (!t) return NULL;
    t->type = type;
    t->value = value ? ft_strdup(value) : NULL;
    return t;
}

void token_free(void *tokptr)
{
    t_token *t = (t_token*)tokptr;
    if (!t) return;
    free(t->value);
    free(t);
}

/* Helper: read a quoted chunk and append to buffer */
static int append_piece(char **buf, const char *piece)
{
    char *joined;

    if (!*buf)
        *buf = ft_strdup(piece);
    else
    {
        joined = ft_strjoin(*buf, piece);
        free(*buf);
        *buf = joined;
    }
    return (*buf ? 0 : -1);
}

static int read_quoted(const char *s, int i, char quote, char **buf)
{
    int start = ++i; /* skip opening quote */
    while (s[i] && s[i] != quote)
        i++;
    if (!s[i]) {
        fprintf(stderr, "minishell: unclosed quote\n");
        return -1;
    }
    char *piece = ft_substr(s, start, (size_t)(i - start));
    if (!piece || append_piece(buf, piece) < 0) { free(piece); return -1; }
    free(piece);
    return i + 1; /* skip closing */
}

/* Read a WORD token respecting quotes */
static int read_word(const char *s, int i, char **out)
{
    char *buf = NULL;

    while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>", s[i]))
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            int ni = read_quoted(s, i, s[i], &buf);
            if (ni < 0) { free(buf); return -1; }
            i = ni;
        }
        else
        {
            int start = i;
            while (s[i] && !ft_isspace((unsigned char)s[i]) && !ft_strchr("|<>", s[i]) && s[i] != '\'' && s[i] != '\"')
                i++;
            char *piece = ft_substr(s, start, (size_t)(i - start));
            if (!piece || append_piece(&buf, piece) < 0) { free(piece); free(buf); return -1; }
            free(piece);
        }
    }
    *out = buf ? buf : ft_strdup("");
    return i;
}

/* Main lexer */
t_list *tokenize(const char *line)
{
    t_list *tokens = NULL;
    int i = 0;

    if (!line) return NULL;
    while (line[i])
    {
        i = skip_spaces(line, i);
        if (!line[i]) break;

        if (line[i] == '|')
        {
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_PIPE, "|")));
            i++;
        }
        else if (line[i] == '>' && line[i+1] == '>')
        {
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_APPEND, ">>")));
            i += 2;
        }
        else if (line[i] == '>')
        {
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_REDIR_OUT, ">")));
            i++;
        }
        else if (line[i] == '<' && line[i+1] == '<')
        {
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_HEREDOC, "<<")));
            i += 2;
        }
        else if (line[i] == '<')
        {
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_REDIR_IN, "<")));
            i++;
        }
        else
        {
            char *word = NULL;
            int ni = read_word(line, i, &word);
            if (ni < 0) { ft_lstclear(&tokens, token_free); return NULL; }
            ft_lstadd_back(&tokens, ft_lstnew(token_new(T_WORD, word)));
            free(word);
            i = ni;
        }
    }
    return tokens;
}

/* Build argv containing only WORD tokens (simple command) */
char **tokens_to_argv_words(t_list *tokens)
{
    size_t count = 0, idx = 0;
    t_list *cur = tokens;
    while (cur)
    {
        t_token *t = (t_token*)cur->content;
        if (t && t->type == T_WORD) count++;
        cur = cur->next;
    }
    char **argv = (char**)malloc(sizeof(char*) * (count + 1));
    if (!argv) return NULL;

    cur = tokens;
    while (cur)
    {
        t_token *t = (t_token*)cur->content;
        if (t && t->type == T_WORD)
            argv[idx++] = ft_strdup(t->value);
        cur = cur->next;
    }
    argv[idx] = NULL;
    return argv;
}

void free_argv(char **argv)
{
    size_t i = 0;
    if (!argv) return;
    while (argv[i]) { free(argv[i]); i++; }
    free(argv);
}
