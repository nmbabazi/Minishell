/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tableau.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/10 13:55:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t		ft_array_len(char **tab)
{
	size_t i;
	
	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**ft_array_delone(char **tab, int nb)
{
	char **new;
	int i;
	int l;

	i = 0;
	l = 0;
	if (!(new = malloc(sizeof(char *) * ft_array_len(tab))))
		return (NULL);
	while (tab[i])
	{
		if (i == nb)
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
	return (new);
}