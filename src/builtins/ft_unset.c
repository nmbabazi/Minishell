/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:56:26 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/19 15:41:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_error_variable_unset(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[++i] && cmd[i] != '=')
	{
		if (cmd[i] != '_' && (cmd[i] < 'A' ||
			cmd[i] > 'Z') && (cmd[i] < 'a' || cmd[i] > 'z')
			&& (cmd[i] < '0' || cmd[i] > '9'))
		{
			g_status = 1;
			if (g_pid > 0)
				return (1);
			return (ft_error("minishell: unset: « ", cmd,
			" » : not a valid identifier\n"));
		}
	}
	return (0);
}

int		ft_error_var_unset(char *cmd)
{
	if (*cmd != '_' && *cmd != '=' &&
		(*cmd < 'A' || *cmd > 'Z') &&
		(*cmd < 'a' || *cmd > 'z'))
	{
		g_status = 1;
		if (g_pid > 0)
			return (1);
		return (ft_error("minishell: unset: « ", cmd,
		" » : not a valid identifier\n"));
	}
	if (ft_error_variable_unset(cmd) != 0)
		return (1);
	g_status = 0;
	return (0);
}

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
	if (!cmd_builtin[1])
		return (ft_error("", NULL, NULL));
	while (cmd_builtin[i])
	{
		if (ft_strchr(cmd_builtin[i], '=') && g_pid == 0)
		{
			g_status = 1;
			return (ft_error("minisell : unset: « ", cmd_builtin[1],
			" »: identifiant non valable\n"));
		}
		if (ft_error_var_unset(cmd_builtin[i]) == 0)
		{
			g_export = ft_del_element_lst(g_export, cmd_builtin[i]);
			g_env = ft_del_element_lst(g_env, cmd_builtin[i]);
		}
		i++;
	}
	g_status = 0;
	return (0);
}
