#include "../../include/minishell.h"

void     ft_verif_permission(char *cmd)
{
    struct stat mystat;

    errno = 0;
    stat(cmd, &mystat);
	if ((mystat.st_mode & S_IFMT) == S_IFREG && strncmp(cmd, "./", 2) == 0)
	{
		if (!((mystat.st_mode & S_IFMT) == S_IXUSR))
		{
			ft_error("minishell: ", cmd, ": Permission denied\n");
			exit(126);
		}
	}
}

int		exec_cmd(t_sh *sh)
{
	int	status;
	
	g_fork = 1;
	g_pid = 0;
	status = g_status;
	g_pid = fork();
	if (g_pid < 0)
		ft_strerror("fork : ");
	else if (g_pid > 0)
	{
		if (waitpid(g_pid, &status, 0) == -1)
			return(ft_str_error("minishell: ", "wait", NULL));
		g_status = WEXITSTATUS(status);
		if (WIFSTOPPED(status))
			g_status = WSTOPSIG(status);
		else if (WIFSIGNALED(status))
			g_status = WTERMSIG(status);
		if (status == 127)
			g_status = 127;
		if (WTERMSIG(status) == 3)
			g_status = 131;
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		g_fork = 0;
		kill(g_pid, SIGTERM);
	}
	else
	{
		if (sh->pars.out || sh->pars.in)
			if(ft_deal_redir(sh) != 0)
				exit(g_status);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		else if (sh->cmd[0])
		{
			ft_get_path_absolute(g_env, sh);
			if (execve(sh->cmd[0], sh->cmd, g_env_tab) == -1)
			{
				ft_verif_permission(sh->cmd[0]);
				ft_error("minishell: ", sh->cmd[0], ": command not found\n");
				exit(127);
			}
		}
		exit(g_status);
	}
	return (0);
}