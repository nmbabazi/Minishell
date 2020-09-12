/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/12 16:22:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int   ft_spaceredirection(char *str)
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
        if ((str[i] == '>'  && i == 0) || (str[i] == '>'  && str[i - 1] != '>') || (str[i] == '<'))
        {
            n++;
            i++;
            if (str[i] == '>')
                i++;
            while(str[i] == ' ')
            {
                str[i] = '\t';
                i++;
            }
        }
        i++;
    }
    return (n);
}

char    *ft_startisolation(char *str, char *p, int i, int l)
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
        if (((str[i] == '>'  && i == 0) || (str[i] == '>'  && str[i - 1] != '>') || (str[i] == '<')) && ft_activslash(str, i) == 0)
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

char    *ft_isolateredirection(char *str, int nb_redir)
{
    char *p;
    int len;
    int i;
    int l;

    len = ft_strlen(str) + nb_redir;
    i = 0;
    l = 0;
    if (!(p = calloc((len + 1), sizeof(char))))
        return (NULL);
    p = ft_startisolation(str, p, i, l);
    return (p);
}

int     checksorti(char *line)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;
    while (line[i])
    {
        if (line[i] == '>')
        {
            cnt = 0;
            while (line[i] == '>')
            {
                i++;
                cnt++;
            }
            while (line[i] == ' ')
                i++;
            if (cnt > 2 || ft_isalnum(line[i]) == 0)
                return (0);
        }
        i++;
    }
    return (1);
}

int     checkentre(char *line)
{
    int i;
    int cnt;

    i = 0;
    cnt = 0;
    while (line[i])
    {
        if (line[i] == '<')
        {
            cnt = 0;
            while (line[i] == '<')
            {
                i++;
                cnt++;
            }
            while (line[i] == ' ')
                i++;
            if (cnt > 1 || ft_isalnum(line[i]) == 0)
                return (0);
        }
        i++;
    }
    return (1);
}