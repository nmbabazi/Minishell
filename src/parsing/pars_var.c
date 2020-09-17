/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/17 18:28:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_cleanvar(char *var)
{
	int i; 
	//int l;
	//char *ret;
	
	i = 0;
	if (!var)
		return ;
	//l = 0;
	//if (!(ret = malloc(sizeof(char) * ft_strlen(var) + 1)))
	//	return (NULL);
	while (var[i])
	{
		if (var[i] == ' ')
			var[i] = '\t';
		i++;
	}
	
}

int ft_isvarname(char c)
{
    if (ft_isalnum(c) == 1 || (c != '\"' && c != '$' && c != '!' && c != '@' && c != '\n'
            && c != '|' && c != ',' && c != '&' && c != '\\' && c != ' ' && c != '\''))
        return (1);
    return (0);
}

static int     ft_namesize(char *src)
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

static int     add_varsize(char *src)
{
    int i;
    char *name;
    int cnt;
    int len;
    char *var;

    i = 0;
    name = NULL;
    len = 0;
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

static char    *ft_cpyvar(char *str, char *ret, int i, int l)
{
    int cnt;
    char *name;
    char *var;

    cnt = 0;
    name = NULL;
    var = NULL;
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
        if ((str[i] == '$' && ft_activslash(str, i) == 0)
            && (ft_isvarname(str[i + 1]) == 1 || str[i + 1] == '?') && str[i + 1])
        {
            cnt = ft_namesize(&str[i + 1]);
            name = ft_strvardup(&str[i + 1], cnt);
            var = ft_get_var_parsing(g_env, name);
            ret = ft_strcat(ret, var);
            free(name);
            free(var);
            i += (cnt + 1);
            l = ft_strlen(ret);
        }
        if (str[i] && str[i] != '\'' && (str[i] != '$' || !str[i + 1] || ft_isvarname(str[i + 1]) == 0 || (str[i] == '$' && ft_activslash(str, i) == 1)))
        {
            ret[l] = str[i];
            i++;
        }
        l++;
    }
    return (ret);
}

char    *ft_getactivvar(char *str)
{
    int len;
    char *ret;
    int i;
    int l;

    ret = NULL;
    i = 0;
    l = 0;
    len = add_varsize(str) + ft_strlen(str);
    if (!(ret = calloc((len + 1), sizeof(char))))
        return (NULL);
    ret = ft_cpyvar(str, ret, i, l);
    free(str);
    return (ret);
}