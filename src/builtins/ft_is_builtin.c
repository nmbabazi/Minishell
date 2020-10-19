/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:50:43 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/19 15:36:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_is_bultin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
	ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
	ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
	ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	return (FALSE);
}
