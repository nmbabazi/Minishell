/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:43:24 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/17 15:02:19 by ejawe            ###   ########.fr       */
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
	while (cmd_builtin[i] && ft_is_n_option(cmd_builtin[i]) == 1)
	{
		n++;
		i++;
	}
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
