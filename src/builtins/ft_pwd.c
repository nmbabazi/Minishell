#include "../../include/minishell.h"

int    ft_pwd(char **cmd_builtin)
{
    char path[PATH_MAX];

    (void)cmd_builtin;
    if (!(getcwd(path, PATH_MAX)))
        return (ft_strerror(""));
    else if (g_pid == 0)
    {
        ft_putstr_fd(path, 2);
        ft_putstr_fd("\n", 2);
    }
    return (0);
}