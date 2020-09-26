#include "../../include/minishell.h"

int     ft_error_var_export(char *cmd)
{
	int i;
	if (*cmd != '_' &&
        *cmd != '=' &&
        (*cmd < 'A' || *cmd > 'Z') &&
        (*cmd < 'a' || *cmd > 'z'))
        {
            g_status = 1;
            errno = 1;
            if (g_pid > 0)
                return (1);
            return(ft_error("minishell: export: « ", cmd, 
            " » : identifiant non valable\n"));
        }
	i = 0;
	while (cmd[++i] && cmd[i] != '=')
		if (cmd[i] != '_' &&
            (cmd[i] < 'A' || cmd[i] > 'Z') &&
            (cmd[i] < 'a' || cmd[i] > 'z') &&
            (cmd[i] < '0' || cmd[i] > '9'))
        {
            g_status = 1;
            errno = 1;
            if (g_pid > 0)
                return (1);
            return(ft_error("minishell: export: « ", cmd, 
            " » : identifiant non valable\n"));
        }
	return (0);
}

void    ft_replace(t_list *export, char *newcmd, char *var)
{
    t_list  *next;
    char    *tmp;
    int     len_var;

    len_var = ft_strlen(var);
    if(ft_strchr(var, '='))
        len_var--;
    while(export)
    {
        next = export->next;
        if(ft_strncmp(export->content, var, len_var) == 0)
        {
            tmp = export->content;
            export->content = ft_strdup(newcmd);
            free(tmp);
            return ;
        }
        export = next;
    }
}

int    ft_create_var(char *newvar, t_list **list)
{
	t_list	*temp;

	temp = NULL;
	if (!(temp = malloc(sizeof(t_list))))
		return (1);
	if (!(temp->content = ft_strdup(newvar)))
		return (1);
	temp->next = 0;
	ft_lstadd_back(list, temp);
	return(0);
}

int     ft_add_var(char *newvar)
{
    if (newvar[0] == '=' && g_pid > 0)
    {
        g_status = 1;
        return (ft_error("minishell: export: « ", newvar, 
        " » : identifiant non valable\n"));
    }
    ft_create_var(newvar, &g_export);
    if (ft_strchr(newvar, '='))
    {
        ft_create_var(newvar, &g_env);
        free_array(g_env_tab);
        g_env_tab = ft_lststring_to_tab(g_env);
    }
    return(0);
}

char    *ft_var_cmd(char *cmd)
{
    int i;
    char *var;

    i = 0;
    var = NULL;
    while (cmd[i] != '=' && cmd[i])
        i++;
    //if (ft_strchr(cmd, '='))
    if (cmd[i] == '=')
        i++;
    var = ft_substr(cmd, 0, i);
    return (var);
}

int     ft_export(char **cmd_builtin)
{
    int i;
    char *var;
    int j;

    if (!cmd_builtin[1])
        return (ft_rank_export(g_export));
    i = 1;
    j = 0;
    while (cmd_builtin[i] && ft_error_var_export(cmd_builtin[i]) == 0)
    {
        var = ft_var_cmd(cmd_builtin[i]);
        if (ft_surch_var(g_export, var))
        {
            if (ft_strchr(var, '='))
            {
                ft_replace(g_export, cmd_builtin[i], var);
                ft_replace(g_env, cmd_builtin[i], var);
            }
        }
        else
        {
            ft_add_var(cmd_builtin[i]);
        }
        i++;
        free(var);
    }
    return (0);
}