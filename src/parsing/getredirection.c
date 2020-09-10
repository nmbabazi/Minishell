/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getredirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/10 13:54:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	ft_add_file(char *cmd, t_list **out, int type)
{
	int i;

	i = 1;
	if (cmd[i] == '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	ft_lstadd_back(out, ft_lstnew(malloc_redir(&cmd[i], type)));
	return ;
}

void    ft_getredir(char **cmd, t_sh *sh)
{
	int i;
	
	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' && cmd[i][1] != '>')
			ft_add_file(cmd[i], &sh->pars.out, 1);
		if (cmd[i][0] == '>' && cmd[i][1] == '>')
			ft_add_file(cmd[i], &sh->pars.out, 2);
		if (cmd[i][0] == '<')
			ft_add_file(cmd[i], &sh->pars.in, 1);
		i++;
	}
}

void	ft_printredir(t_list *lst)
{
	t_redir *actual_redir;

	while (lst)
	{
		actual_redir = lst->content;
		ft_putstr(actual_redir->str);
		ft_putnbr(actual_redir->type);
		ft_putstr("\n");
		lst = lst->next;
	}
}

static	void	ft_dell_backslash(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\\' && (cmd[i][1] == '>' || cmd[i][1] == '<'))
			cmd[i][0] = 127;
		i++;
	}
}

int		ft_isredirected(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	ft_array_cpy(char **new, char **tab)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (tab[i])
	{
		if (tab[i][0] == '>' || tab[i][0] == '<')
			free(tab[i]);
		else
		{
			new[l] = tab[i];
			l++;
		}
		i++;
	}
	new[l] = NULL;
	free(tab);
}

char	**ft_dell_redir(char **cmd)
{
	size_t len;
	char **new;

	len = ft_array_len(cmd);
	if (ft_isredirected(cmd) == 0)
		return (cmd);
	if (!(new = malloc(sizeof(char *) * len)))
		return (NULL);
	ft_array_cpy(new, cmd);
	return (new);
}

char    **ft_cleancmd(char **cmd, t_sh *sh)
{
	sh->pars.in = NULL;
	sh->pars.out = NULL;
	ft_getredir(cmd, sh);
	printf("---------------sorti--------------\n");
	ft_printredir(sh->pars.out);
	printf("---------------entre--------------\n");
	ft_printredir(sh->pars.in);
	cmd = ft_dell_redir(cmd);
	ft_dell_backslash(cmd);
	return (cmd);
}
