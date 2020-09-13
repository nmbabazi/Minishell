#include "../../include/minishell.h"
int     ft_update_pwd(void)
{
    char *old_pwd;
    char *pwd;
    char *all_pwd;
    char *all_old_pwd;

    pwd = NULL;
    old_pwd = NULL;
    all_pwd = NULL;
    all_old_pwd = NULL;
    old_pwd = ft_get_var(g_env, "PWD=");
    pwd = getcwd(pwd, 0);
    if (!old_pwd || !pwd)
        ft_strerror("");
    all_pwd = ft_strjoin("PWD=", pwd);
    all_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
    ft_replace(g_env, all_pwd, "PWD=");
    ft_replace(g_env, all_old_pwd, "OLDPWD=");
    ft_replace(g_export, all_pwd, "PWD=");
    ft_replace(g_export, all_old_pwd, "OLDPWD=");
    free(pwd);
    free(old_pwd);
    free(all_pwd);
    free(all_old_pwd);
}

int    ft_cd(t_list *list, char **cmd_builtin)
{
    char *home;
    int nb;

    nb = ft_lentab(cmd_builtin);
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
    if(g_pid > 0)
        ft_update_pwd();
    return (errno);
}
