/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/28 15:32:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_isvarname(char c)
{
	if (ft_isalnum(c) == 1 || (c != '\"' && c != '[' && c != ']'
		&& c != '$' && c != '!' && c != '@' && c != '\n'
			&& c != '|' && c != ',' && c != '&' && c != '\\'
			&& c != ' ' && c != '\t' && c != '\''))
		return (1);
	return (0);
}

char	*ft_strcat_norm(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!src)
		return (dest);
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}

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
