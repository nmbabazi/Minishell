/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/12 15:15:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mute_sgl_in_dbl(char *str)
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
				if (str[i] == '\'')
				{
					str[i] = 11;
				}
				i++;
			}
		}
		i++;
	}
}

void	unmute_sgl_in_dbl(char *str)
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
				if (str[i] == 11)
				{
					str[i] = '\'';
				}
				i++;
			}
		}
		i++;
	}
}

int		ft_isvarname(char c)
{
	if (ft_isalnum(c) == 1 || (c != '\"' && c != '[' && c != ']'
		&& c != '$' && c != '!' && c != '@' && c != '\n'
			&& c != '|' && c != ',' && c != '&' && c != '\\'
			&& c != ' ' && c != '\t' && c != '\'' && c != '#'
			&& c != '%' && c != '*' && c != '=' && c != '+' && c != '{'
			&& c != '}' && c != '[' && c != ']' && c != ':' && c != '.'))
		return (1);
	return (0);
}

int		ft_isvar(char *str, int i)
{
	if ((str[i] == '$' && ft_activslash(str, i) == 0)
		&& (ft_isvarname(str[i + 1]) == 1
		|| str[i + 1] == '?') && str[i + 1])
		return (1);
	return (0);
}

int		ft_verifstring(char *str, int i)
{
	if (str[i] && (str[i] != '\'' || (str[i] == '\''
		&& ft_activslash(str, i) == 1)) && (str[i] != '$'
		|| !str[i + 1] || ft_isvarname(str[i + 1]) == 0
		|| (str[i] == '$' && ft_activslash(str, i) == 1)))
		return (1);
	return (0);
}
