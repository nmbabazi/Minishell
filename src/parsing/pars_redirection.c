/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 11:46:05 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_spaceredirection_norm(char *str, int i, int n)
{
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
			i += (ft_passsinglequote(&str[i]));
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
			i += (ft_passdblquote(&str[i]));
		if ((str[i] == '>' && i == 0) || (str[i] == '>' && str[i - 1] != '>')
			|| (str[i] == '<'))
		{
			n++;
			i++;
			if (str[i] == '>')
				i++;
			while (str[i] == ' ')
			{
				str[i] = '\t';
				i++;
			}
		}
		i++;
	}
	return (n);
}

int		ft_spaceredirection(char *str)
{
	int i;
	int n;
	int ret;

	i = 0;
	n = 0;
	ret = ft_spaceredirection_norm(str, i, n);
	return (ret);
}

int		ft_isredirection(char *str, int i)
{
	if (((str[i] == '>' && i == 0) || (str[i] == '>' && str[i - 1] != '>')
		|| (str[i] == '<')) && ft_activslash(str, i) == 0)
		return (1);
	return (0);
}

char	*ft_startisolation(char *str, char *p, int i, int l)
{
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
		{
			p = ft_cpysignlequote(str, p, i);
			i += (ft_passsinglequote(&str[i]));
			l = ft_strlen(p);
		}
		if (str[i] == '\"' && ft_activslash(str, i) == 0)
		{
			p = ft_cpydblquote(str, p, i);
			i += (ft_passdblquote(&str[i]));
			l = ft_strlen(p);
		}
		if (ft_isredirection(str, i) == 1)
		{
			p[l] = ' ';
			l++;
			p[l] = str[i];
		}
		p[l] = str[i];
		i++;
		l++;
	}
	return (p);
}

char	*ft_isolateredirection(char *str, int nb_redir)
{
	char	*p;
	int		len;
	int		i;
	int		l;

	len = ft_strlen(str) + nb_redir;
	i = 0;
	l = 0;
	if (!(p = calloc((len + 1), sizeof(char))))
		return (NULL);
	p = ft_startisolation(str, p, i, l);
	return (p);
}
