#include "../../include/minishell.h"

int    ft_exit(char **cmd_builtin)
{
    if (g_pid == 0)
        ft_putstr_fd("exit\n", 1);
    exit(errno);
    return (0);
}