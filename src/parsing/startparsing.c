/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/23 20:44:37 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     ft_is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0)
            return (1);
    return (0);
}

int     ft_checktocken(char *str, int i, char c)
{
    if (i == 0)
        return (0);
    i--;
    while(i > 0 && str[i] != c)
    {
        if (str[i] != ' ')
            return (1);
        i--;
    }
    if (str[i] == c)
        return (0);
    return (1);
}

int     ft_check_nbcmd(char *line, char c)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' && ft_activslash(line, i) == 0)
            i += (ft_passsinglequote(&line[i]));
        if (line[i] == '\"' && ft_activslash(line, i) == 0)
            i += (ft_passdblquote(&line[i]));
        if (line[i] == c)
        {
            if (ft_checktocken(line, i, c) == 0)
                return (0);
        }
        i++;
    }
    return (1);
}

int     ft_openquote(char *src)
{
    int n;
    int i;

    n = 0;
    i = 0;
    while (src && src[i])
    {
        if (src[i] == '\'' && ft_activslash(src, i) == 0)
        {
            n++;
            i += ft_passsinglequote(&src[i]);
            if (src[i] != '\'')
                return (1);
            n++;
        }
        if (src[i] == '\"' && ft_activslash(src, i) == 0)
        {
            n++;
            i += ft_passdblquote(&src[i]);
            if (src[i] != '\"')
                return (1);
            n++;
        }
        i++;
    }
    if ((n % 2) != 0)
        return (1);
    return (0);
}

char    **ft_parse(char *line, t_sh *sh)
{
    int nb_cmd;
    char **cmd;

    nb_cmd = 0;
    if (ft_openquote(line) == 1 || ft_activslash(line, ft_strlen(line)) == 1)
    {
        g_status = 1;
        ft_strerror("minishell : open quote");
        return (NULL);
    }
    if (checksorti(line) == 0 || checkentre(line) == 0)
    {
        g_status = 1;        
        ft_str_error("minishell :" , NULL , "erreur de syntaxe près du symbole inattendu « > »");
        return (NULL);
    }
    line = ft_parscmd(line);
    //printf("PARSED LINE %s\n", line);
    cmd = ft_split(line, ' ');
    free(line);
    ft_addback_space(cmd);
    //printf("---------------avant redir--------------\n");
    //ft_printcmd(cmd);
    cmd = ft_cleancmd(cmd, sh);
    //printf("---------------apres redir--------------\n");
    ft_printcmd(cmd);
    return (cmd) ;
}