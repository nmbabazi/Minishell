/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:43:24 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/14 12:37:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_is_n_option(char *cmd_builtin)
{
	int i;

	i = 1;
	if (cmd_builtin[0] != '-')
		return (0);
	while (cmd_builtin[i])
	{
		if (cmd_builtin[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int		ft_echo(char **cmd_builtin)
{
	int i;
	int n;

	i = 1;
	n = 0;
	g_status = 0;
	if (g_pid > 0)
		return (0);
	if (cmd_builtin[1] && ft_is_n_option(cmd_builtin[1]) == 1)
		n = 1;
	if (cmd_builtin[1] && ft_strcmp(cmd_builtin[1], "-n") == 0)
		n = 1;
	i = i + n;
	while (cmd_builtin[i] && ft_strcmp(cmd_builtin[i], "-n") == 0)
		i++;
	while (cmd_builtin[i])
	{
		ft_putstr_fd(cmd_builtin[i], 1);
		if (cmd_builtin[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
