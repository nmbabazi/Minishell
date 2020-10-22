/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:41:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/22 19:21:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_deal_nothing(int nb)
{
	(void)nb;
	if (g_fork == 0)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
	}
	else
	{
		ft_putstr("Quit (core dumped)\n");
		g_status = 131;
	}
	return ;
}

void	ft_insensitive_typing(int nb)
{
	(void)nb;
	if (g_fork == 2)
		ft_putstr("\n");
	if (g_fork == 0)
	{
		ft_putstr("\n");
		ft_putstr("$> ");
	}
	if (g_read == 1 || g_str)
	{
		free(g_line);
		free(g_str);
		g_str = NULL;
		g_str = ft_strnew(0);
	}
	g_status = 130;
}
