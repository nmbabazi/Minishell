#include "../../include/minishell.h"

int     ft_len_var(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=' && str[i])
        i++;
    return (i);
}

t_list  *ft_del_element_lst(t_list *list, char *var)
{    
    t_list  *tmp;
    t_list  *previous;
    
    if (list == NULL) 
        return (list);
    previous = list;
    if (ft_strncmp(previous->content, var, ft_len_var(previous->content)) == 0 &&
    ft_len_var(previous->content) == ft_strlen(var))
    {
        list = previous->next;
        ft_lstdelone(previous, free);
        return (list);
    }
    tmp = previous->next;
    while(tmp != NULL)
    {
        if (ft_strncmp(tmp->content, var, ft_len_var(tmp->content)) == 0 &&
        ft_len_var(tmp->content) == ft_strlen(var))
        {
            previous->next = tmp->next;
            ft_lstdelone(tmp, free);
            return (list);
        }
        previous = tmp;
        tmp = tmp->next;
    }
    return (list);
}

int     ft_unset(char **cmd_builtin)
{
    char *var;
    int i;

    i = 1;
    if (!cmd_builtin[1])
    {
        if (g_pid > 0)
            return (0);
        return(ft_error("", NULL, NULL));
    }
    while (cmd_builtin[i])
    {
        if (ft_strchr(cmd_builtin[i], '=') && g_pid == 0)
        {
            g_status = 1;
            return (ft_error("minisell : unset: « ", cmd_builtin[1], " »: identifiant non valable\n"));
        }
        if(ft_error_var_export(cmd_builtin[i]) == 0)
        {
            g_export = ft_del_element_lst(g_export, cmd_builtin[i]);
            g_env = ft_del_element_lst(g_env, cmd_builtin[i]);
        }
        i++;
    }
    return (0);
}