/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:49:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/21 21:18:24 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_str_is_digit(char *str)
{
	int i;
	int nb;
	int space;

	i = 0;
	nb = 0;
	space = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ')
			return (0);
		if (ft_isdigit(str[i]) == 1)
			nb = 1;
		if (str[i] == ' ' && nb == 1)
			space = 1;
		if (ft_isdigit(str[i]) == 1 && space == 1)
			return (0);
		i++;
	}
	return (1);
}

int		ft_exit(char **cmd_builtin)
{
	if (g_pid > 0)
		ft_putstr_fd("exit\n", 1);
	if (cmd_builtin[1])
	{
		if (ft_str_is_digit(cmd_builtin[1]) == 0)
		{
			if (g_pid > 0)
				ft_error("minishell: exit: ", cmd_builtin[1],
				": numeric argument required\n");
			g_status = 2;
			exit(g_status);
		}
		else
			g_status = ft_atoi(cmd_builtin[1]) % 256;
	}
	if (cmd_builtin[1] && cmd_builtin[2])
	{
		if (ft_str_is_digit(cmd_builtin[1]) == 1)
			g_status = 1;
		if (g_pid > 0)
			ft_error("minishell: exit: ", NULL,
			"too many arguments\n");
		return (0);
	}
	exit(g_status);
	return (0);
}
