/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:41:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/23 16:10:45 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **cmd_builtin)
{
	g_status = 0;
	if (!cmd_builtin[1] && g_pid == 0)
		ft_lstprint(g_env);
	else if (cmd_builtin[1] && g_pid > 0)
	{
		g_status = 127;
		return (ft_error("minishell: env: «", cmd_builtin[1],
		"» : No such file or directory\n"));
	}
	return (0);
}
