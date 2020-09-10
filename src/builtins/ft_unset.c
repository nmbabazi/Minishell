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
    
    // si la liste est NULL on s'arrete
    if (list == NULL) 
        return (list);
    previous = list;
    //printf("var = %s\n", var);
    //printf("content = %s\n", previous->content);
    //printf("len_var = %d\n", ft_len_var(previous->content));
    //printf("strcpm = %d\n", ft_strncmp(previous->content, var, ft_strlen(previous->content)));

    // Verifie la tete de liste, cas particulier
    if (ft_strncmp(previous->content, var, ft_len_var(previous->content)) == 0 &&
    ft_len_var(previous->content) == ft_strlen(var))
    {
        //printf("OK 1\n");
        list = previous->next;
        ft_lstdelone(previous, free);
        return (list);
    }
    tmp = previous->next; // le cas n est gere on se place donc sur le cas n+1
    while(tmp != NULL) // On Mouline est on supprime si on trouve l'element
    {
        if (ft_strncmp(tmp->content, var, ft_len_var(tmp->content)) == 0 &&
        ft_len_var(tmp->content) == ft_strlen(var))
        {
            //printf("OK 2\n");
            previous->next = tmp->next;
            ft_lstdelone(tmp, free);
            return (list);
        }
        previous = tmp; // pour ce souvenir dans la prochaine iteration du precedent
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
        return(ft_strerror(""));
    while (cmd_builtin[i])
    {
        if(ft_error_var_export(cmd_builtin[i]))
        {
            g_export = ft_del_element_lst(g_export, cmd_builtin[i]);
            g_env = ft_del_element_lst(g_env, cmd_builtin[i]);
        }
        i++;
    }
    return (0);
}