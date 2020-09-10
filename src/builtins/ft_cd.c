#include "../../include/minishell.h"
int     ft_update_pwd(void)
{
    char *old_dir;
    char *dir;

    dir = NULL;
    old_dir = NULL;
    old_dir = ft_get_var(g_env, "OLDPWD");
    dir = getcwd(dir, PATH_MAX);
    if (!old_dir || !dir)
        ft_strerror("");
    ft_replace(g_env, "PATH", dir);
    ft_replace(g_env, "OLDPATH", old_dir);
    ft_replace(g_export, "PATH", dir);
    ft_replace(g_export, "OLDPATH", old_dir);
    free(dir);
    free(old_dir);
}

int    ft_cd(t_list *list, char **cmd_builtin)
{
    char *home;
    int nb;

    nb = ft_lentab(cmd_builtin);
    printf("nb = %d\n", nb);
    if (nb == 1)
    {
        if (!(home = ft_get_var(g_env, "HOME=")))
        {
            ft_putstr_fd("cd: HOME not set\n", 1);
            return (1);
        }
        if ((chdir(home)) == -1)
            return (ft_strerror("home: home"));
        free(home);
    }
    if (nb > 1)
    {
        if (cmd_builtin[1] == "")
            return (0);
        if (chdir(cmd_builtin[1]) == -1)
            return (ft_strerror("minishell: "));
    }
    ft_update_pwd();
    return (errno);
}
