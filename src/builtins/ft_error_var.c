/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:47:48 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/21 23:32:15 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_error_variable(char *cmd, char *msg)
{
	int	i;

	i = 0;
	while (cmd[++i] && cmd[i] != '=')
	{
		if (cmd[i] != '_' && (cmd[i] < 'A' ||
			cmd[i] > 'Z') && (cmd[i] < 'a' || cmd[i] > 'z')
			&& (cmd[i] < '0' || cmd[i] > '9'))
		{
			g_status = 1;
			if (g_pid > 0)
				return (1);
			return (ft_error(msg, cmd,
			" » : not a valid identifier\n"));
		}
	}
	return (0);
}

int		ft_error_var(char *cmd, char *msg)
{
	if (*cmd != '_' && *cmd != '=' &&
		(*cmd < 'A' || *cmd > 'Z') &&
		(*cmd < 'a' || *cmd > 'z'))
	{
		g_status = 1;
		if (g_pid > 0)
			return (1);
		return (ft_error(msg, cmd,
		" » : not a valid identifier\n"));
	}
	if (ft_error_variable(cmd, msg) != 0)
		return (1);
    if (!g_status)
	    g_status = 0;
	return (0);
}