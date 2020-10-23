/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 16:17:00 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_param(t_sh *sh)
{
	sh->is_pipe = 0;
	g_read = 0;
	sh->d = 0;
}

void	ft_join_n_dup(t_sh *sh)
{
	g_line = ft_join_n_free(g_line, g_str);
	g_str = ft_dup_n_free(g_str, g_line);
	sh->d = 1;
}

int		ft_get_next_cmd(t_sh *sh)
{
	ft_putstr_fd("$> ", 2);
	while ((sh->ret = get_next_line(1, &g_line)) >= 0)
	{
		if (g_read && sh->ret == 0)
			ft_join_n_dup(sh);
		if (g_read && sh->ret > 0)
		{
			if (g_sig && sh->d == 0)
				ft_deal_line();
			if (sh->d == 1)
			{
				g_line = ft_join_n_free(g_line, g_str);
				ft_free_n_null(&g_str);
				g_str = ft_strnew(0);
			}
			ft_init_param(sh);
			ft_get_cmd(g_line, sh);
			ft_putstr_fd("$> ", 2);
		}
		else if (sh->ret == 0 && !g_read)
			break ;
		ft_free_n_null(&g_line);
	}
	return (sh->ret);
}

int		main(int ac, char **av, char **envp)
{
	t_sh sh;
	int ret;

	ret = 0;
	(void)ac;
	(void)av;
	ft_init(&sh, envp);
	//ft_rank_export(g_export);
	signal(SIGQUIT, ft_deal_nothing);
	signal(SIGINT, ft_insensitive_typing);
	if (ac == 3 && !ft_strcmp(av[1], "-c"))//////////////////
	{
		ft_get_cmd(av[2], &sh);
	}
	else
	{
		ret = ft_get_next_cmd(&sh);
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(g_status);
		}
		if (ret == -1)
			exit(errno);
	}
	free_all();
	return (g_status);
}
