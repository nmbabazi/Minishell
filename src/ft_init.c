#include "../include/minishell.h"

void    ft_init(t_sh *sh, char **envp)
{
    sh->cmd = NULL;
	sh->path = NULL;
	sh->last_pipe = 0;
	sh->is_pipe = 0;
	g_env = NULL;
	g_env = ft_tab_to_list(&g_env, envp);
	g_export = ft_tab_to_list(&g_export, envp);
}