/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startparsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/05 11:48:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_checktocken(char *str, int i, char c)
{
	if (i == 0)
		return (0);
	i--;
	if (c == '|' && str[i] == '|')
		return (1);
	while (i > 0 && str[i] != c)
	{
		if (str[i] != ' ')
			return (1);
		i--;
	}
	if (str[i] == c)
		return (0);
	return (1);
}

int		ft_check_nbcmd(char *line, char c)
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

int		ft_openquote_norm(char *src, int i, int n)
{
	while (src && src[i])
	{
		if (src[i] == '\'' && ft_activslash(src, i) == 0)
		{
			n++;
			if (ft_passsinglequote(&src[i]) == -1)
				return (1);
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

int		ft_openquote(char *src)
{
	int n;
	int i;
	int ret;

	n = 0;
	i = 0;
	ret = ft_openquote_norm(src, i, n);
	return (ret);
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

char	**ft_parse(char *line, t_sh *sh)
{
	int		nb_cmd;
	char	**cmd;

	nb_cmd = 0;
	if (ft_openquote(line) == 1 || ft_activslash(line, ft_strlen(line)) == 1)
	{
		g_status = 1;
		ft_error("minishell :", NULL, "open quote\n");
		return (NULL);
	}
	if (checksorti(line) == 0 || checkentre(line) == 0)
	{
		g_status = 2;
		ft_error("minishell :", NULL, "syntax error near unexpected token\n");
		return (NULL);
	}
	line = ft_parscmd(line);
	cmd = ft_split(line, ' ');
	free(line);
	//ft_printcmd(cmd);
	ft_addback_space(cmd);
	ft_delate_quote(cmd);
	cmd = ft_cleancmd(cmd, sh);
	g_status = 0;
	return (cmd);
}
