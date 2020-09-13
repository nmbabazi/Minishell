#include "../../include/minishell.h"

int    ft_env(char **cmd_builtin)
{
    if (!cmd_builtin[1] && g_pid > 0)
        ft_lstprint(g_env);
    else
        return(ft_strerror("env: "));
    return(0);
}