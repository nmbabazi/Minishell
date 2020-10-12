/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/12 15:14:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_error_pipe(char *line, int i)
{
	if (line[i + 1] == '\0' && line[i] == '|')
	{
		ft_error("minishell : erreur de syntaxe\n", NULL, NULL);
		g_status = 1;
		return (1);
	}
	return (0);
}

int		ft_str_error(char *cmd_name, char *arg, char *msg)
{
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (errno == 2)
		errno = 1;
	else if (errno == 13)
		errno = 1;
	return (errno);
}

int		ft_error(char *cmd_name, char *arg, char *msg)
{
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	return (1);
}
