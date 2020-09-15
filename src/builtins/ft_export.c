#include "../../include/minishell.h"

int     ft_error_var_export(char *cmd)
{
	int i;

    if (g_pid > 0)
        return (1);
	if (*cmd != '_' &&
    *cmd != '=' &&
    (*cmd < 65 || *cmd > 90) &&
    (*cmd < 97 || *cmd > 122))
		return (ft_strerror("minisell: export : not a valid identifer : "));
	i = 0;
	while (cmd[++i] && cmd[i] != '=')
		if (cmd[i] != '_' &&
        (cmd[i] < 65 || cmd[i] > 90) &&
        (cmd[i] < 97 || cmd[i] > 122) &&
        (cmd[i] < 48 || cmd[i] > 57))
			return (ft_strerror("minisell: export : not a valid identifer : "));
	return (1);
}

void    ft_replace(t_list *export, char *newcmd, char *var)
{
    t_list  *next;
    char    *tmp;
    int     len_var;
    //char *str = NULL;

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
            //str = export->content;
            //printf("content = %s\n", str);
            free(tmp);
            //free(str);
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
	return (0);
}

void    ft_add_var(char *newvar)
{
    ft_create_var(newvar, &g_export);
    if (ft_strchr(newvar, '='))
        ft_create_var(newvar, &g_env);
}

char    *ft_var_cmd(char *cmd)
{
    int i;
    char *var;

    i = 0;
    var = NULL;
    while (cmd[i] != '=' && cmd[i])
        i++;
    if (ft_strchr(cmd, '='))
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
    while (cmd_builtin[i] && ft_error_var_export(cmd_builtin[i]))
    {
        var = ft_var_cmd(cmd_builtin[i]);
        if (ft_surch_var(g_export, var))
            ft_replace(g_export, cmd_builtin[i], var);
        else
            ft_add_var(cmd_builtin[i]);
        i++;
        free(var);
    }
    return (0);
}