/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 00:29:21 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_join_n_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s2, s1);
	free(tmp);
	tmp = NULL;
	return (s1);
}

char	*ft_dup_n_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strdup(s2);
	free(tmp);
	return (s1);
}

int		ft_get_next_cmd(t_sh *sh)
{
	int		ret;
	char	*line;
	char	*str;
	int		d;

	line = NULL;
	ret = 0;
	g_read = 0;
	d = 0;
	ft_putstr_fd("$> ", 2);
	str = ft_strnew(0);

	while ((ret = get_next_line(1, &line)) >= 0)
	{
		if (g_read == 1 && ret == 0)
		{
			line = ft_join_n_free(line, str);
			str = ft_dup_n_free(str, line);
			d = 1;
		}
		if (g_read == 1 && ret > 0)
		{
			if (d == 1)
			{
				line = ft_join_n_free(line, str);
				free(str);
				str = NULL;
				str = ft_strnew(0);
			}
			sh->is_pipe = 0;
			ft_get_cmd(line, sh);
			ft_putstr_fd("$> ", 2);
			g_read = 0;
			d = 0;
		}
		else if (ret == 0 && g_read == 0)
			break ;
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	free(line);
	line = NULL;
	free(str);
	str = NULL;
	return (ret);
}

int		main(int ac, char **av, char **envp)
{
	t_sh sh;
	int ret;

	ret = 0;
	(void)ac;
	(void)av;
	ft_init(&sh, envp);
	ft_rank_export(g_export);
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
