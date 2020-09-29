/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/29 11:53:01 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_namesize(char *src)
{
	int i;

	i = 0;
	if (src[i] == '?')
	{
		i = 1;
		return (i);
	}
	while (src[i])
	{
		if (ft_isvarname(src[i]) != 1)
			break ;
		i++;
	}
	return (i);
}

int		add_varsize(char *src, int i, int len)
{
	char	*name;
	int		cnt;
	char	*var;

	name = NULL;
	var = NULL;
	while (src[i])
	{
		if (src[i] == '\'' && ft_activslash(src, i) == 0)
			i += (ft_passsinglequote(&src[i]));
		if ((src[i] == '$' && ft_activslash(src, i) == 0)
			&& (ft_isvarname(src[i + 1]) == 1 || src[i + 1] == '?'))
		{
			cnt = ft_namesize(&src[i + 1]);
			name = ft_strvardup(&src[i + 1], cnt);
			var = ft_get_var_parsing(g_env, name);
			len += ft_strlen(var);
			free(name);
			free(var);
			i += cnt;
		}
		i++;
	}
	return (len);
}

char	*ft_addvar(char *str, int i)
{
	int		cnt;
	char	*name;
	char	*var;

	name = NULL;
	var = NULL;
	cnt = ft_namesize(&str[i + 1]);
	name = ft_strvardup(&str[i + 1], cnt);
	var = ft_get_var_parsing(g_env, name);
	free(name);
	return (var);
}

char	*ft_cpyvar(char *str, char *ret, int i, int l)
{
	while (str[i])
	{
		if (str[i] == '\'' && ft_activslash(str, i) == 0)
		{
			ret = ft_cpysignlequote(str, ret, i);
			i += ft_passsinglequote(&str[i]);
			l = ft_strlen(ret);
			ret[l] = str[i];
			i++;
			l++;
		}
		if (ft_isvar(str, i) == 1)
		{
			ret = ft_strcat_norm(ret, ft_addvar(str, i));
			i += (ft_namesize(&str[i + 1]) + 1);
			l = ft_strlen(ret);
		}
		if (ft_verifstring(str, i) == 1)
		{
			ret[l] = str[i];
			i++;
		}
		l++;
	}
	return (ret);
}

char	*ft_getactivvar(char *str)
{
	int		len;
	char	*ret;
	int		i;
	int		l;

	ret = NULL;
	i = 0;
	l = 0;
	mute_sgl_in_dbl(str);
	len = add_varsize(str, i, l) + ft_strlen(str);
	if (!(ret = calloc((len + 1), sizeof(char))))
		return (NULL);
	ret = ft_cpyvar(str, ret, i, l);
	unmute_sgl_in_dbl(ret);
	free(str);
	return (ret);
}
