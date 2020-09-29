/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 11:39:14 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cleanquote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
		{
			str[i] = 11;
			i += (ft_passsinglequote(&str[i]));
			str[i] = 11;
		}
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
		{
			str[i] = 15;
			i += (ft_passdblquote(&str[i]));
			str[i] = 15;
		}
		i++;
	}
	return ;
}

void	ft_addback_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 11 || str[i] == 15)
			str[i] = ' ';
		i++;
	}
}

char	*ft_delate_backslash(char *str)
{
	int		len;
	int		i;
	int		l;
	char	*ret;

	i = 0;
	l = 0;
	len = ft_strlen(str);
	if (!(ret = calloc(sizeof(char), len + 1)))
		return (NULL);
	while (str[i])
	{
		if (str[i] == 127)
		{
			i++;
		}
		else
		{
			ret[l] = str[i];
			i++;
			l++;
		}
	}
	free(str);
	return (ret);
}

char	*ft_cpyandclean(char *str)
{
	int		len;
	int		i;
	int		l;
	char	*ret;

	i = 0;
	l = 0;
	len = ft_strlen(str);
	if (!(ret = calloc(sizeof(char), len + 1)))
		return (NULL);
	while (str[i])
	{
		if (str[i] == 11 || str[i] == 15)
		{
			i++;
		}
		else
		{
			ret[l] = str[i];
			i++;
			l++;
		}
	}
	free(str);
	return (ret);
}

char	*ft_parscmd(char *str)
{
	int nb_redir;

	nb_redir = ft_addspace(str);
	str = ft_isolateredirection(str, nb_redir);
	str = ft_getactivvar(str);
	nb_redir = ft_addspace(str);
	ft_cleanquote(str);
	ft_cleanbackslash(str);
	str = ft_delate_backslash(str);
	return (str);
}
