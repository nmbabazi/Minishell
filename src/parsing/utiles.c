/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/10 15:15:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_initpars(t_sh *sh)
{
	sh->pars.in = NULL;
	sh->pars.out = NULL;
}

char	*ft_strvardup(const char *s, int n)
{
	int		i;
	char	*new_string;

	i = 0;
	if (!(new_string = malloc(sizeof(char) * (n + 2))))
		return (0);
	while (s[i] && i < n)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '=';
	i++;
	new_string[i] = '\0';
	return (new_string);
}

char    *ft_get_var_parsing(t_list *list, char *var)
{
	t_list *next;

	if(ft_strncmp("?=", var, ft_strlen(var)) == 0)
		return(ft_substr("0", 0, 1));
	while(list)
	{
		next = list->next;
		if(ft_strncmp(list->content, var, ft_strlen(var)) == 0)
			return(ft_substr(list->content, ft_strlen(var), ft_strlen(list->content) - ft_strlen(var)));
		list = next;
	}
	return(NULL);
}

int		ft_len_cmd(char *line, int i, int begin)
{
	int len;

	len = 0;
	if (line[i + 1] == '\0' && line[i] != ';')
		len = (i + 1) - begin;
	else
		len = i - begin;
	return (len);
}

int		ft_isspace(char *line, int index)
{
	while (line[index] == ' ' && line[index])
		index++;
	return (index);
}