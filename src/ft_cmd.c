#include "../include/minishell.h"

void	ft_cmd(char *cmd, t_sh *sh)
{
	//printf("pipe = %d\n", sh->is_pipe);
	//printf("last_pipe = %d\n", sh->last_pipe);
	//printf("cmd = %s\n", cmd);
	if ((sh->cmd = ft_parse(cmd, sh)) == NULL || g_status > 0)
	{
		free(cmd);
		return ;
	}
	//printf("cmd apres parse = %s\n", cmd);
	if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "export") == 0)
		sh->is_export = 1;
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("");
	else if((sh->is_pipe == 1 || sh->last_pipe == 1) && sh->is_export == 0)
	{
		if (sh->cmd[0])
			ft_get_path_absolute(g_env, sh);
		ft_exec_pipe(sh, sh->cmd);
	}
	else if ((sh->is_pipe == 0 && sh->last_pipe == 0))
		exec_cmd(sh);
	free_array(sh->cmd);
	ft_lstclear(&sh->pars.out, lst_free_redir);
	ft_lstclear(&sh->pars.in, lst_free_redir);
	free(cmd);
	cmd = NULL;
}
