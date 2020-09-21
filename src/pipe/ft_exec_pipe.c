#include "../../include/minishell.h"

void		ft_exec_pipe(t_sh *sh, char **cmd)
{
	pipe(sh->fd);
	if ((sh->pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (sh->pid == 0)
	{
		dup2(sh->fdd, 0);
		if (sh->last_pipe == 0)
			dup2(sh->fd[1], 1);
		close(sh->fd[0]);
		if (sh->pars.out || sh->pars.in)
			ft_deal_redir(sh);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		else if (sh->cmd[0])
		{
			if(execve(cmd[0], cmd, g_env_tab) == -1)
			exit(ft_strerror("minishell : "));
		}
		exit(1);
	}
	else
	{
		wait(NULL);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		close(sh->fd[1]);
		sh->fdd = sh->fd[0];
	}
}
