#include "minishell.h"

void    cmd_pwd(void)
{
    char    path[PATH_MAX];

    if (getcwd(path, sizeof(path)) != NULL)
        printf("%s\n", path);
    else
        perror("pwd");
}

/* echo builtin:
   - supports multiple -n flags (e.g., -n -n)
   - prints joined args separated by spaces
*/
int     cmd_echo(char **argv)
{
    int i = 1;
    int no_newline = 0;
    int j;

    /* parse -n (one or more) */
    while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
    {
        j = 2;
        while (argv[i][j] == 'n') j++;
        if (argv[i][j] != '\0') break; /* not only n's */
        no_newline = 1;
        i++;
    }
    for (; argv[i]; ++i)
    {
        fputs(argv[i], stdout);
        if (argv[i+1]) fputc(' ', stdout);
    }
    if (!no_newline) fputc('\n', stdout);
    return 0;
}

int     cmd_exit(void)
{
    /* For now, always exit 0 (no args parsing). */
    exit(0);
}
