/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 15:56:43 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_deal_pipe_child(t_sh *sh)
{
	dup2(sh->fdd, 0);
	if (sh->last_pipe == 0)
		dup2(sh->fd[1], 1);
	close(sh->fd[0]);
	if (sh->pars.out || sh->pars.in)
		if (ft_deal_redir(sh) == -1)
			exit(g_status);
	if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
		ft_exec_builtin(sh->cmd);
	else if (sh->cmd[0])
	{
		ft_get_path_absolute(sh);
		ft_verif_permission(sh->cmd[0]);
		if (execve(sh->cmd[0], sh->cmd, g_env_tab) == -1)
		{
			ft_is_file(sh->cmd[0]);
			ft_error("minishell: ", sh->cmd[0], ": command not found\n");
			g_status = 127;
			exit(127);
		}
	}
}

void	ft_deal_pipe_parent(t_sh *sh)
{
	close(sh->fd[1]);
	sh->fdd = sh->fd[0];
}

void	ft_deal_last_pipe(int status)
{
	int pid;

	pid = 0;
	while (pid != -1)
		pid = waitpid(g_pid, &status, 0);
	ft_deal_status(status);
	g_fork = 0;
}

int		ft_exec_pipe(t_sh *sh)
{
	int	status;

	g_fork = 2;
	g_pid = 0;
	status = g_status;
	pipe(sh->fd);
	if ((g_pid = fork()) < 0)
		ft_str_error("fork : ", NULL, NULL);
	else if (g_pid > 0)
	{
		if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "exit") != 0 &&
		ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(sh->cmd);
		ft_deal_pipe_parent(sh);
	}
	else
	{
		ft_deal_pipe_child(sh);
		exit(g_status);
	}
	if (sh->last_pipe == 1)
		ft_deal_last_pipe(status);
	return (0);
}
