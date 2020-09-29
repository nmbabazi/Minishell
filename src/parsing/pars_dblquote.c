/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dblquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 15:45:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_passdblquote(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
			break ;
		i++;
	}
	return (i);
}

void	ft_spaceindblquote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
			i += (ft_passsinglequote(&str[i]));
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
		{
			i++;
			while (str[i])
			{
				if (str[i] == '\"' && ft_activslash(str, i) == 0)
					break ;
				if (str[i] == ' ')
				{
					str[i] = '\t';
				}
				i++;
			}
		}
		i++;
	}
	return ;
}

char	*ft_cpydblquote(char *src, char *dest, int i)
{
	int l;

	l = ft_strlen(dest);
	dest[l] = src[i];
	i++;
	l++;
	while (src[i])
	{
		if (src[i] == '\"' && ft_activslash(src, i) == 0)
			break ;
		dest[l] = src[i];
		l++;
		i++;
	}
	return (dest);
}

int		ft_escapechar_quote(char c)
{
	if (c == '$' || c == '\"' || c == '\\' || c == '`')
		return (1);
	return (0);
}

void	ft_cleanbackslash_inquote(char *str)
{
	int i;
	int bool;

	i = 0;
	bool = 0;
	while (str[i])
	{
		if (str[i] == 15)
		{
			i++;
			while (str[i] != 15)
			{
				if (str[i] == '\\' && bool == 0 &&
					ft_escapechar_quote(str[i + 1]) == 1)
				{
					str[i] = 127;
					bool = 1;
				}
				if (str[i] == '\\' && bool == 1)
					bool = 0;
				i++;
			}
		}
		i++;
	}
}
