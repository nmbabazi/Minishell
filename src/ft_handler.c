/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:41:32 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/23 15:13:03 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_deal_line(void)
{
	free(g_line);
	g_line = ft_strnew(0);
	g_sig = 0;
}

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
	if (g_read == 1)
	{
		g_sig = 1;
		free(g_line);
		free(g_str);
		g_str = NULL;
		g_str = ft_strnew(0);
	}
	g_status = 130;
}
