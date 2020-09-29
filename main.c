#include "include/minishell.h"

/* A faire
//
// echo || echo
// status 127 si cmd not found
//
// ->test cmd/cmd
// echo\t\v\f\r�123456789:;=?@AB...
// 
//
//echo a | export A=a; echo $A
//export A=a | cat; echo $A
//
//
// echo $'A'
*/

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
		//printf("g_status1 = %d\n", g_status);
		//status = WEXITSTATUS(status);
		g_status = WEXITSTATUS(status);
		//printf("g_status2 = %d\n", g_status);
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
		//printf("g_status3 = %d\n", g_status);
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
				//printf("errno = %d\n", errno);
				ft_verif_permission(sh->cmd[0]);
				/*if (errno == 13 || errno == 8)
				{
					ft_str_error("minishell: ", sh->cmd[0], ": ");
					g_status = 126;
					exit (126);
				}*/
				ft_error("minishell: ", sh->cmd[0], ": command not found\n");
				exit(127);
			}
		}
		exit(g_status);
	}
}

int     main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
    char    *line;
    int     ret;
    t_sh    sh;
	
	ft_init(&sh, envp);
	ft_rank_export(g_export);
    line = NULL;
    ret = 0;
	signal(SIGQUIT, ft_deal_nothing);
	signal(SIGINT, ft_insensitive_typing);
	if(ac == 3 && !ft_strcmp(av[1], "-c"))
	{
		ft_get_cmd(av[2], &sh);
	}
	else 
	{
		ft_putstr_fd("$> ", 2);

		while ((ret = get_next_line(1, &line)) > 0)
		{
			sh.is_pipe= 0;
			ft_get_cmd(line, &sh);
			free(line);
			line = NULL;
			ft_putstr_fd("$> ", 2);
		}
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(errno);
		}
		if (ret == -1)
			exit(errno);
		free(line);
		line = NULL;
	}
    free_all(envp, &sh);
    return (g_status);
}