/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/10 15:24:10 by user42           ###   ########.fr       */
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

int     ft_checktocken(char *str, int i)
{
    if (i == 0)
        return (0);
    i--;
    while(i > 0 && str[i] != ';')
    {
        if (str[i] != ' ')
            return (1);
        i--;
    }
    if (str[i] == ';')
        return (0);
    return (1);
}

int     ft_check_nbcmd(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' && ft_activslash(line, i) == 0)
            i += (ft_passsinglequote(&line[i]));
        if (line[i] == '\"' && ft_activslash(line, i) == 0)
            i += (ft_passdblquote(&line[i]));
        if (line[i] == ';')
        {
            if (ft_checktocken(line, i) == 0)
            {
                ft_putstr_fd("parse error ;\n", 2);
                return (0);
            }
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
        }
        if ((src[i] == '\"') && ft_activslash(src, i) == 0)
            n++;
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
        ft_putstr_fd("open quote\n", 2);
            return (NULL);
    }
    if (checksorti(line) == 0 || checkentre(line) == 0)
    {
        ft_putstr_fd("syntax error ' >' \n", 2);
            return (NULL);
    }
    if ((nb_cmd = ft_check_nbcmd(line)) == 0)
        return (NULL);
    line = ft_parscmd(line);
    printf("PARSED LINE %s\n", line);
    cmd = ft_split(line, ' ');
    free(line);
    ft_addback_space(cmd);
    ft_printcmd(cmd);
    cmd = ft_cleancmd(cmd, sh);
    ft_printcmd(cmd);
    return (cmd) ;
}
