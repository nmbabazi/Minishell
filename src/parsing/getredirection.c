/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getredirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/20 10:55:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_namedup(const char *s, int n)
{
	int		i;
	char	*new_string;

	i = 0;
	if (!(new_string = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (s[i] && i < n)
	{
		if (s[i] == 6)
			new_string[i] = '>';
		else if (s[i] == 5)
			new_string[i] = '<';
		else 
			new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	new_string = ft_cpyandclean(new_string);
	return (new_string);
}

void	ft_add_file(char *cmd, t_list **out, int type)
{
	int		i;
	char	*name;
	
	i = 1;
	name = NULL;
	if (cmd[i] == '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == 15 || cmd[i] == 11)
		name = ft_namedup(&cmd[i + 1], ft_strlen(&cmd[i + 1]) - 1);
	else
		name = ft_namedup(&cmd[i], ft_strlen(&cmd[i]));
	ft_lstadd_back(out, ft_lstnew(malloc_redir(name, type)));
	free (name);
	return ;
}

void	ft_getredir(char **cmd, t_sh *sh)
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
	size_t	len;
	char	**new;

	len = ft_array_len(cmd);
	if (ft_isredirected(cmd) == 0)
		return (cmd);
	if (!(new = malloc(sizeof(char *) * len)))
		return (NULL);
	ft_array_cpy(new, cmd);
	return (new);
}

void	ft_add_redir_in_var(char **cmd)
{
	int i;
	int l;
	
	i = 0;
	l = 0;
	while (cmd[i])
	{
		ft_swapchar(cmd[i], 6, '>');
		ft_swapchar(cmd[i], 5, '<');
		i++;
	}
}

char	**ft_cleancmd(char **cmd, t_sh *sh)
{
	sh->pars.in = NULL;
	sh->pars.out = NULL;
	ft_getredir(cmd, sh);
	cmd = ft_dell_redir(cmd);
	ft_dell_backslash(cmd);
	ft_add_redir_in_var(cmd);
	return (cmd);
}
