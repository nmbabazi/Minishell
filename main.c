/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/01 13:16:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_get_next_cmd(t_sh *sh)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = 0;
	ft_putstr_fd("$> ", 2);
	while ((ret = get_next_line(1, &line)) > 0)
	{
		sh->is_pipe = 0;
		ft_get_cmd(line, sh);
		free(line);
		line = NULL;
		ft_putstr_fd("$> ", 2);
	}
	if (ret == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(errno);
	}
	if (ret == -1)
		exit(errno);
	free(line);
	line = NULL;
}

int		main(int ac, char **av, char **envp)
{
	t_sh sh;

	(void)ac;
	(void)av;
	ft_init(&sh, envp);
	ft_rank_export(g_export);
	signal(SIGQUIT, ft_deal_nothing);
	signal(SIGINT, ft_insensitive_typing);
	if (ac == 3 && !ft_strcmp(av[1], "-c"))
	{
		ft_get_cmd(av[2], &sh);
	}
	else
		ft_get_next_cmd(&sh);
	free_all(envp, &sh);
	return (g_status);
}
