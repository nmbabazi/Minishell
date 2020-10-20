/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/20 11:28:19 by user42           ###   ########.fr       */
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
