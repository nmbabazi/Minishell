/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 18:48:24 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_deal_child(t_sh *sh)
{
	if (sh->pars.out || sh->pars.in)
		if (ft_deal_redir(sh) != 0)
			exit(g_status);
	if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
		ft_exec_builtin(g_env, sh->cmd);
	else if (sh->cmd[0])
	{
		ft_get_path_absolute(sh);
		ft_verif_permission(sh->cmd[0]);
		if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "./minishell") == 0)
			ft_shlvl(sh->cmd);
		if (execve(sh->cmd[0], sh->cmd, g_env_tab) == -1)
		{
			ft_is_file(sh->cmd[0]);
			ft_error("minishell: ", sh->cmd[0], ": command not found\n");
			g_status = 127;
			exit(127);
		}
	}
}

int		exec_cmd(t_sh *sh)
{
	int	status;

	g_fork = 1;
	g_pid = 0;
	status = g_status;
	if ((g_pid = fork()) < 0)
		ft_str_error("fork : ", NULL, NULL);
	else if (g_pid > 0)
	{
		if (waitpid(g_pid, &status, 0) == -1)
			return (ft_str_error("minishell: ", "wait", NULL));
		ft_deal_status(status);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "./minishell") == 0)
			ft_shlvl(sh->cmd);
		g_fork = 0;
		kill(g_pid, SIGTERM);
	}
	else
	{
		ft_deal_child(sh);
		exit(g_status);
	}
	return (0);
}
