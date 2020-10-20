/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/19 18:57:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		checksorti(char *line)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '\'' && ft_activslash(line, i) == 0)
			i += (ft_passsinglequote(&line[i]));
		if (line[i] == '\"' && ft_activslash(line, i) == 0)
			i += (ft_passdblquote(&line[i]));
		if (line[i] == '>')
		{
			cnt = 0;
			while (line[i] == '>')
			{
				i++;
				cnt++;
			}
			while (line[i] == ' ')
				i++;
			if (cnt > 2 || !line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int		checkentre(char *line)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '\'' && ft_activslash(line, i) == 0)
			i += (ft_passsinglequote(&line[i]));
		if (line[i] == '\"' && ft_activslash(line, i) == 0)
			i += (ft_passdblquote(&line[i]));
		if (line[i] == '<')
		{
			cnt = 0;
			while (line[i] == '<')
			{
				i++;
				cnt++;
			}
			while (line[i] == ' ')
				i++;
			if (cnt > 1 || !line[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int		ft_isredirected(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	ft_dell_backslash(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\\' && (cmd[i][1] == '>' || cmd[i][1] == '<'))
			cmd[i][0] = 127;
		i++;
	}
}
