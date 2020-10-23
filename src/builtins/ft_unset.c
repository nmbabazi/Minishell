/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:56:26 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/23 15:04:44 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_var_here(char *content, char *var)
{
	if (ft_strncmp(content, var, ft_len_var(content)) == 0 &&
	ft_len_var(content) == ft_strlen(var))
		return (1);
	return (0);
}

t_list	*ft_del_element_lst(t_list *list, char *var)
{
	t_list	*tmp;
	t_list	*previous;

	if (list == NULL)
		return (list);
	previous = list;
	if (ft_var_here(previous->content, var) == 1)
	{
		list = previous->next;
		ft_lstdelone(previous, free);
		return (list);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (ft_var_here(tmp->content, var) == 1)
		{
			previous->next = tmp->next;
			ft_lstdelone(tmp, free);
			return (list);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (list);
}

int		ft_unset(char **cmd_builtin)
{
	int		i;

	i = 1;
	g_status = 0;
	if (!cmd_builtin[1])
		return (ft_error("", NULL, NULL));
	while (cmd_builtin[i])
	{
		if (ft_strchr(cmd_builtin[i], '='))
		{
			g_status = 1;
			if (g_pid > 0)
				return (ft_error("minisell : unset: « ", cmd_builtin[1],
				" »: not a valid identifier\n"));
		}
		if (ft_error_var(cmd_builtin[i], "minisell : unset: « ") == 0)
		{
			g_export = ft_del_element_lst(g_export, cmd_builtin[i]);
			g_env = ft_del_element_lst(g_env, cmd_builtin[i]);
		}
		i++;
	}
	return (0);
}
