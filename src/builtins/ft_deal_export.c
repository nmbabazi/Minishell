/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deal_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:47:48 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/12 15:07:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_error_variable_export(char *cmd)
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
			return (ft_error("minishell: export: « ", cmd,
			" » : not a valid identifier\n"));
		}
	}
	return (0);
}

int		ft_error_var_export(char *cmd)
{
	if (*cmd != '_' && *cmd != '=' &&
		(*cmd < 'A' || *cmd > 'Z') &&
		(*cmd < 'a' || *cmd > 'z'))
	{
		g_status = 1;
		if (g_pid > 0)
			return (1);
		return (ft_error("minishell: export: « ", cmd,
		" » : not a valid identifier\n"));
	}
	if (ft_error_variable_export(cmd) != 0)
		return (1);
	g_status = 0;
	return (0);
}

void	ft_print_export(char *var, char *str)
{
	char *value;

	ft_putstr_fd("declare -x ", 1);
	ft_putstr(var);
	if (ft_strchr(str, '='))
	{
		value = ft_get_var(g_export, var);
		ft_putstr("\"");
		ft_putstr(value);
		ft_putstr("\"");
		free(value);
	}
	ft_putstr("\n");
}

void	ft_lstprint_rank_export(t_list *lst)
{
	char	*var;
	int		i;
	char	*str;

	i = 0;
	if (!lst || g_pid == 0)
		return ;
	while (lst)
	{
		str = lst->content;
		if (!(str[0] == '_' && str[1] == '='))
		{
			while (str[i] != '=' && str[i])
				i++;
			var = ft_substr(str, 0, i + 1);
			ft_print_export(var, str);
			free(var);
		}
		lst = lst->next;
		i = 0;
	}
}

int		ft_rank_export(t_list *export)
{
	t_list	*begin;
	char	*tmp;
	int		rank;

	begin = export;
	rank = 1;
	while (rank)
	{
		rank = 0;
		while (export)
		{
			while (export->next &&
				ft_strcmp(export->content, export->next->content) > 0)
			{
				tmp = export->content;
				export->content = export->next->content;
				export->next->content = tmp;
				rank = 1;
			}
			export = export->next;
		}
		export = begin;
	}
	ft_lstprint_rank_export(g_export);
	return (0);
}
