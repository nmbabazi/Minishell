/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/22 16:22:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int   ft_spaceafterslash(char *str)
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
        if (str[i] == ' ' && ft_activslash(str, i) == 1)
            str[i] = '\t';
        i++;
    }
    return (n);
}

int    ft_addspace(char *str)
{
    int i;

    i = 0;
    ft_spaceinsglquote(str);
    ft_spaceindblquote(str);
    ft_spaceafterslash(str);
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
    while (i >= 0 && src[i] == '\\')
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
            str[i] = 15;
            i += (ft_passdblquote(&str[i]));
            str[i] = 15;
        }
        i++;
      //  printf("char -%c- indicde %d\n", str[i], i);
    }
    return ;
}

int     ft_escapechar_quote(char c)
{
    if (c == '$' || c == '\"' || c == '\\' || c == '`')
        return (1);
    return (0);
    
}

int     ft_escapechar(char c)
{
    if (ft_isascii(c) == 1 && c != '>' && c != '<')
        return (1);
    return (0);
    
}

void    ft_addback_quote(char *str)
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

void    ft_cleanbackslash_inquote(char *str)
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
                if (str[i] == '\\' && bool == 0 && ft_escapechar_quote(str[i + 1]) == 1)
                {
                    str[i] = 127;
                    bool = 1;
                }
                if (str[i] == '\\' &&  bool == 1)
                    bool = 0;
                i++;
            }
        }
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
        if (str[i] == 15) 
        {
            i++;
            while (str[i] != 15)
                i++;
        }
        if (str[i] == '\\' && bool == 0 && ft_escapechar(str[i + 1]) == 1)
        {
            str[i] = 11;
            bool = 1;
        }
        if (str[i] != '\\'  &&  bool == 1)
            bool = 0;
        i++;
    }
    ft_cleanbackslash_inquote(str);
    return ;
}

char    *ft_cpy_cleaned(char *str)
{
    int len;
    int i;
    int l;
    char *ret;

    i = 0;
    l = 0;
    len = ft_strlen(str);
    if (!(ret = calloc(sizeof(char), len + 1)))
        return (NULL);
    while (str[i])
    {
        if (str[i] == 11 || str[i] == 15 || str[i] == 127)
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

char    *ft_parscmd(char *str)
{
    int nb_redir;

    //printf("entering %s\n", str);
    nb_redir = ft_addspace(str);  //enregister les espaces in quote active
    //printf("befor redi %s\n", str);
    str = ft_isolateredirection(str, nb_redir); // isoler les redirections (hors quote actives) par des espaces
    //printf("befor var %s\n", str);
    str = ft_getactivvar(str);        // recuperer les variable (hors '' actives)
    //printf("befor tab %s\n", str);
    nb_redir = ft_addspace(str);
    //printf("la %s\n", str);
    ft_cleanquote(str);      // virer les quote a virer
    //printf("befor tab %s\n", str);
    ft_cleanbackslash(str);  // virer les backslash a virer
    //printf("befor tab %s\n", str);
    str = ft_cpy_cleaned(str);
    return (str);
}

void    ft_printcmd(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        printf("%d--%s--\n", i, cmd[i]);
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