#include "../../include/minishell.h"

/*voir afficher les variables d'env, exite ou pas ?*/

int    ft_echo(char **cmd_builtin)
{
    int i;
    int n;

    i = 1;
    n = 0;
    g_status = 0;
    if (g_pid > 0)
        return (0);
    if (cmd_builtin[1] && ft_strcmp(cmd_builtin[1], "-n") == 0)
        n = 1;
    i = i + n;
    while (cmd_builtin[i] && ft_strcmp(cmd_builtin[i], "-n") == 0)
        i++;
    while (cmd_builtin[i])
    {
        ft_putstr_fd(cmd_builtin[i], 1);
        if (cmd_builtin[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n)
        ft_putstr_fd("\n", 1);
    return (0);
}