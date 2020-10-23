/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:47:02 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/23 15:07:10 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_builtin(char **cmd_builtin)
{
	g_status = 0;
	if (ft_strcmp(cmd_builtin[0], "cd") == 0)
		ft_cd(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "pwd") == 0)
		ft_pwd(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "echo") == 0)
		ft_echo(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "exit") == 0)
		ft_exit(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "env") == 0)
		ft_env(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "export") == 0)
		ft_export(cmd_builtin);
	else if (ft_strcmp(cmd_builtin[0], "unset") == 0)
		ft_unset(cmd_builtin);
}
