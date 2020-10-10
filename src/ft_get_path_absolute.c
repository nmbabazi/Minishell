/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_absolute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/07 12:47:00 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_verif_path(char *bin)
{
	struct stat mystat;

	errno = 0;
	stat(bin, &mystat);
	if (errno)
		return (1);
	if ((mystat.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_error("minishell: ", bin, ": Is a directory\n");
		exit(126);
	}
	return (0);
}

void	ft_check_path(char **path_split, t_sh *sh)
{
	char	*bin;
	int		i;

	bin = NULL;
	i = 0;
	while (path_split[i])
	{
		if (!(bin = (char *)ft_calloc(sizeof(char),
		(ft_strlen(path_split[i]) + 1 + ft_strlen(sh->cmd[0]) + 1))))
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, sh->cmd[0]);
		if (ft_verif_path(bin) == 0)
		{
			free(sh->cmd[0]);
			sh->cmd[0] = bin;
			break ;
		}
		free(bin);
		bin = NULL;
		i++;
	}
}

int		ft_get_path_absolute(t_sh *sh)
{
	char **path_split;

	if (!(sh->path = ft_get_var(g_env, "PATH=")))
	{
		g_status = 127;
		if (g_pid == 0)
			ft_error("minishell: ", sh->cmd[0],
			": No such file or directory\n");
		exit(g_status);
	}
	if (ft_strncmp(sh->cmd[0], "./", 2) == 0)
		ft_verif_path(sh->cmd[0]);
	else if (sh->cmd[0][0] != '/' || ft_strncmp(sh->cmd[0], "./", 2) != 0)
	{
		path_split = ft_split(sh->path, ':');
		ft_check_path(path_split, sh);
		if (path_split)
			free_array(path_split);
		if (sh->path)
		{
			free(sh->path);
			sh->path = NULL;
		}
	}
	return (0);
}
