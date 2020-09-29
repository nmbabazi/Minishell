/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 11:41:42 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_addspace(char *str)
{
	int i;

	i = 0;
	ft_spaceinsglquote(str);
	ft_spaceindblquote(str);
	ft_spaceafterslash(str);
	i = ft_spaceredirection(str);
	return (i);
}

void	ft_addback_space(char **cmd)
{
	int i;
	int l;

	i = 0;
	while (cmd[i])
	{
		l = 0;
		while (cmd[i][l])
		{
			if (cmd[i][l] == '\t')
				cmd[i][l] = ' ';
			l++;
		}
		i++;
	}
}
