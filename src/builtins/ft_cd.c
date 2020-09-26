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
    {
        ft_error("", NULL, NULL);
        g_status = 1;
    }
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
    return(0);
}

int     ft_home(void)
{
    char *home;

    if (!(home = ft_get_var(g_env, "HOME=")))
    {
        if (g_pid > 0)
            ft_putstr_fd("minishell: cd: HOME not set\n", 1);
        return (1);
    }
    if ((chdir(home)) == -1)
        return (ft_strerror("home: home"));
    free(home);
    return (0);
}

int     ft_cd(t_list *list, char **cmd_builtin)
{
    int nb;

    nb = ft_lentab(cmd_builtin);
    if (nb == 1)
    {
        g_status = ft_home();
    }
    else if (nb == 2)
    {
        if (cmd_builtin[1][0] == '\0')
            return (0);
        else if (cmd_builtin[1][0] == '~')
            g_status = ft_home();
        else if (chdir(cmd_builtin[1]) == -1)
        {
           // if (errno == EACCES && g_pid == 0)
            //    g_status = ft_str_error("minishell: cd: ", cmd_builtin[1], ": ");
            if (g_pid == 0)
                g_status = ft_str_error("minishell: cd: ", cmd_builtin[1], ": ");
            //strerror(errno);
            //g_status = errno;
            return (g_status);
        }
    }
    else if (nb > 2)
    {
            if (g_pid > 0)
                ft_error("minishell: cd: ", NULL, 
                "trop d'arguments\n");
            g_status = 1;
        return (g_status);
    }
    if(g_pid > 0)
        ft_update_pwd();
    return (errno);
}
