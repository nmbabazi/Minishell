#include "../include/minishell.h"

void    ft_init(t_sh *sh, char **envp)
{
    sh->cmd = NULL;
	sh->path = NULL;
	sh->last_pipe = 0;
	sh->is_pipe = 0;
	sh->is_export = 0;
	sh->continue_cmd = 0;
	sh->nb_cmd = 0;
	g_status = 0;
	g_env = NULL;
	g_env = ft_tab_to_list(&g_env, envp);
	g_export = ft_tab_to_list(&g_export, envp);
	g_env_tab = ft_lststring_to_tab(g_env);
}