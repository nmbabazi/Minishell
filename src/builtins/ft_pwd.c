/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:51:25 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/01 13:15:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_pwd(char **cmd_builtin)
{
	char path[PATH_MAX];

	(void)cmd_builtin;
	if (!(getcwd(path, PATH_MAX)))
	{
		g_status = ft_str_error("", NULL, NULL);
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
