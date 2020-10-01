/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_permission.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/01 15:57:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_verif_permission(char *cmd)
{
	struct stat permstat;

	errno = 0;
	if (ft_strncmp(cmd, "./", 2) != 0)
		return ;
	stat(cmd, &permstat);
	if (errno)
		return ;
	
	if ((permstat.st_mode & S_IFMT) == S_IFREG)
	{

		if ((permstat.st_mode & S_IXUSR) == 0)
		{
			ft_error("minishell: ", cmd, ": Permission denied\n");
			exit(126);
		}
	}
}

void	ft_is_file(char *cmd)
{
	struct stat permstat;

	errno = 0;
	if (ft_strncmp(cmd, "./", 2) != 0)
		return ;
	stat(cmd, &permstat);
	if (errno)
		return ;
	if ((permstat.st_mode & S_IFMT) == S_IFREG)
	{
		g_status = 0;
		exit(0);
	}
}