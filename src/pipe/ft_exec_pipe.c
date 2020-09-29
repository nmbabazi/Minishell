#include "../../include/minishell.h"

int		ft_exec_pipe(t_sh *sh, char **cmd)
{
	int	status;

	g_fork = 1;
	status = g_status;
	pipe(sh->fd);
	if ((sh->pid = fork()) < 0)
		ft_strerror("fork : ");
	else if (sh->pid == 0)
	{
		dup2(sh->fdd, 0);
		if (sh->last_pipe == 0)
			dup2(sh->fd[1], 1);
		close(sh->fd[0]);
		if (sh->pars.out || sh->pars.in)
			if(ft_deal_redir(sh) == -1)
				exit(g_status);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		else if (sh->cmd[0])
		{
			if(execve(cmd[0], cmd, g_env_tab) == -1)
			{
				ft_error("minishell: ", sh->cmd[0], ": command not found\n");
				g_status = 127;
				exit(127);
			}
		}
		exit(g_status);
	}
	else
	{
		if (waitpid(sh->pid, &status, 0) == -1)
			return(ft_str_error("minishell: ", "wait", NULL));
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
				ft_exec_builtin(g_env, sh->cmd);
		close(sh->fd[1]);
		sh->fdd = sh->fd[0];
		status = WEXITSTATUS(status);
		g_status = WEXITSTATUS(status);
		if (WIFSTOPPED(status))
			g_status = WSTOPSIG(status);
		if (WIFSIGNALED(status))
			g_status = WTERMSIG(status);
		g_fork = 0;
	}
	return (0);
}
