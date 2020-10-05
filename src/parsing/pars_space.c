/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/05 12:00:53 by user42           ###   ########.fr       */
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

int		ft_activslash_dell(char *src, int i)
{
	int n;

	n = 0;
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && (src[i] == '\\' || src[i] == 127))
	{
		i--;
		n++;
	}
	if ((n % 2) != 0)
		return (1);
	return (0);
}
