/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/11 11:13:11 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    ft_addspace(char *str)
{
    int i;

    i = 0;
    ft_spaceinsglquote(str);
    ft_spaceindblquote(str);
    i = ft_spaceredirection(str);
    return (i);
}

int     ft_activslash(char *src, int i)
{
    int n;

    n = 0;
    if (i == 0)
        return (0);
    i--;
    while (i > 0 && src[i] == '\\')
    {
        i--;
        n++;
    }
    if ((n % 2) != 0)
        return (1);
    return (0);
}

void    ft_cleanquote(char *str)
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
            str[i] = ' ';
            i += (ft_passdblquote(&str[i]));
            str[i] = ' ';
        }
        i++;
    }
    return ;
}

int     ft_escapechar(char c)
{
    if (ft_isalnum(c) == 0 && c != '>' && c != '<')
        return (1);
    return (0);
    
}

void    ft_addback_quote(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == 11)
            str[i] = ' ';
        i++;
    }
}

void    ft_cleanbackslash(char *str)
{
    int i;
    int bool;

    i = 0;
    bool = 0;
    while (str[i])
    {
        if (str[i] == 11) 
        {
            i++;
            while (str[i] != 11)
                i++;
        }
        if (str[i] == '\\' && bool == 0 && ft_escapechar(str[i + 1]) == 1)
        {
            str[i] = 127;
            bool = 1;
        }
        if (str[i] == '\\' &&  bool == 1)
            bool = 0;
        i++;
    }
    ft_addback_quote(str);
    return ;
}

char    *ft_parscmd(char *str)
{
    int nb_redir;

    //printf("intput = %s\n", str);
    nb_redir = ft_addspace(str);  //enregister les espaces in quote active
    str = ft_isolateredirection(str, nb_redir); // isoler les redirections (hors quote actives) par des espaces
    str = ft_getactivvar(str);        // recuperer les variable (hors '' actives)
    ft_cleanquote(str);      // virer les quote a virer
    ft_cleanbackslash(str);  // virer les backslash a virer
    return (str);
}

void    ft_printcmd(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        //printf("%d--%s--\n", i, cmd[i]);
        i++;
    }
    
}

void    ft_addback_space(char **cmd)
{
    int i;
    int l;

    i = 0;
    while (cmd[i])
    {
        l = 0;
        while (cmd[i][l])
        {
            if (cmd[i][l] == '\t')
                cmd[i][l] = ' ';
            l++;
        }
        i++;
    }
}