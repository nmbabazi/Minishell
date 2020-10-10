/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deal_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/10 13:01:29 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_deal_status(int status)
{
	g_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		g_status = WSTOPSIG(status);
	if (WIFSIGNALED(status))
		g_status = 128 + WTERMSIG(status);
	if (WTERMSIG(status) == 3)
		g_status = 131;
	if (WTERMSIG(status) == 2 && g_fork == 1)
	 	ft_putstr("\n");
}
