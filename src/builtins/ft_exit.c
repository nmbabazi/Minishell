#include "../../include/minishell.h"

int    ft_exit(char **cmd_builtin)
{
    ft_putstr_fd("exit\n", 1);
    exit(0);
    return (0);
}