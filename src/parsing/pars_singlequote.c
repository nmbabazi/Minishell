/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_singlequote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/10 13:55:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     ft_passsinglequote(char *str)
{
    int i;

    i = 1;
    while (str[i] != '\'' && str[i])
        i++;
    if (!str[i])
        return (-1);
    return (i);
}

void    ft_spaceinsglquote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' && ft_activslash(str, i) == 0)
        {
            i++;
            while (str[i] != '\'')
            {
                if (str[i] == ' ')
                    str[i] = '\t';
                i++;
            }
        }
        i++;
    }
    return;
}

char    *ft_cpysignlequote(char *src, char *dest, int i)
{
    int l;

    l = ft_strlen(dest);
    dest[l] = src[i];
    i++;
    l++;
    while (src[i] != '\'')
    {
        dest[l] = src[i];
        l++;
        i++;
    }
    return (dest);
}