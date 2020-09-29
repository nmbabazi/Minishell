/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:41:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 14:04:44 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **cmd_builtin)
{
	if (!cmd_builtin[1] && g_pid > 0)
		ft_lstprint(g_env);
	else if (cmd_builtin[1] && g_pid > 0)
		return (ft_error("minishell: env: «", cmd_builtin[1],
					"» : Aucun fichier ou dossier de ce type\n"));
	return (0);
}
