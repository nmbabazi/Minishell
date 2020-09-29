/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 11:42:00 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int				ft_spaceafterslash(char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
			i += (ft_passsinglequote(&str[i]));
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
			i += (ft_passdblquote(&str[i]));
		if (str[i] == ' ' && ft_activslash(str, i) == 1)
			str[i] = '\t';
		i++;
	}
	return (n);
}

int				ft_activslash(char *src, int i)
{
	int n;

	n = 0;
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && src[i] == '\\')
	{
		i--;
		n++;
	}
	if ((n % 2) != 0)
		return (1);
	return (0);
}

static	int		ft_escapechar(char c)
{
	if (ft_isascii(c) == 1 && c != '>' && c != '<')
		return (1);
	return (0);
}

static	void	ft_cleanbackslash_norm(char *str, int i, int bool)
{
	while (str[i])
	{
		if (str[i] == 11)
		{
			i++;
			while (str[i] != 11)
				i++;
		}
		if (str[i] == 15)
		{
			i++;
			while (str[i] != 15)
				i++;
		}
		if (str[i] == '\\' && bool == 0 && ft_escapechar(str[i + 1]) == 1)
		{
			str[i] = 127;
			bool = 1;
		}
		if ((str[i] == '\\' && bool == 1) || str[i] != '\\')
			bool = 0;
		i++;
	}
}

void			ft_cleanbackslash(char *str)
{
	int i;
	int bool;

	i = 0;
	bool = 0;
	ft_cleanbackslash_norm(str, i, bool);
	ft_cleanbackslash_inquote(str);
	return ;
}
