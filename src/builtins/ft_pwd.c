/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:51:25 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 13:52:55 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_pwd(char **cmd_builtin)
{
	char path[PATH_MAX];

	(void)cmd_builtin;
	/*if (cmd_builtin[1])
	{
		if (g_pid > 0)
			ft_error("minishell: cd: ", NULL, "trop d'arguments\n");
		g_status = 1;
		return(g_status);
	}*/
	if (!(getcwd(path, PATH_MAX)))
	{
		g_status = ft_strerror("");
		return (g_status);
	}
	else if (g_pid == 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	g_status = 0;
	return (0);
}
