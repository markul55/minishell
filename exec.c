// exec.c
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
static int has_slash(const char *s)
{
    while (s && *s) { if (*s == '/') return 1; s++; }
    return 0;
}

static int is_executable_file(const char *path)
{
    struct stat st;

    if (!path) return 0;
    if (stat(path, &st) != 0) return 0;
    if (!S_ISREG(st.st_mode)) { errno = S_ISDIR(st.st_mode) ? EISDIR : EACCES; return 0; }
    if (access(path, X_OK) != 0) return 0;
    return 1;
}

static char *path_join(const char *dir, const char *cmd)
{
    char *tmp;
    char *full;

    if (!dir || !cmd) return NULL;
    tmp = ft_strjoin(dir, "/");
    if (!tmp) return NULL;
    full = ft_strjoin(tmp, cmd);
    free(tmp);
    return full;
}

static char *search_in_path(const char *cmd)
{
    char    *path = getenv("PATH");
    char   **dirs;
    char    *full = NULL;
    size_t   i = 0;

    if (!path || !*path) return NULL;
    dirs = ft_split(path, ':');
    if (!dirs) return NULL;

    while (dirs[i])
    {
        full = path_join(dirs[i], cmd);
        if (!full) break;
        if (is_executable_file(full))
        {
            // sprzątamy listę dirs i zwracamy full
            size_t j = 0; while (dirs[j]) free(dirs[j++]); free(dirs);
            return full;
        }
        free(full);
        full = NULL;
        i++;
    }
    // sprzątanie
    i = 0; while (dirs[i]) free(dirs[i++]); free(dirs);
    return NULL;
}

/* Zwraca nową ścieżkę lub NULL.
   Jeśli cmd zawiera '/', sprawdza bezpośrednio.
   Jeśli nie, szuka po PATH. */
char *find_executable(const char *cmd)
{
    if (!cmd || !*cmd) return NULL;
    if (has_slash(cmd))
    {
        if (is_executable_file(cmd))
            return ft_strdup(cmd);
        return NULL;
    }
    return search_in_path(cmd);
}

/* Uruchamia zewnętrzny program; zwraca kod wyjścia (0..255), 127/126 dla błędów „shellowych”. */
int run_external(char **argv)
{
    pid_t   pid;
    int     status = 0;
    char   *full = NULL;

    if (!argv || !argv[0]) return 0;

    full = find_executable(argv[0]);
    pid = fork();
    if (pid < 0)
    {
        perror("minishell: fork");
        free(full);
        return 1;
    }
    if (pid == 0)
    {
        // ====== proces dziecka ======
        extern char **environ;

        if (!full)
        {
            // command not found
            fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
            _exit(127);
        }
        execve(full, argv, environ);

        // Jeśli tu jesteśmy, execve się nie udało — ustal sensowny kod:
        if (errno == EACCES || errno == EISDIR)
        {
            fprintf(stderr, "minishell: %s: %s\n", argv[0], strerror(errno));
            _exit(126);
        }
        else if (errno == ENOENT)
        {
            fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
            _exit(127);
        }
        else
        {
            fprintf(stderr, "minishell: %s: %s\n", argv[0], strerror(errno));
            _exit(126);
        }
    }
    // ====== proces rodzica ======
    free(full);
    if (waitpid(pid, &status, 0) < 0)
    {
        perror("minishell: waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status); // np. 130 dla SIGINT
    return 1;
}
