/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:42:06 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/09 11:50:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_addstr(t_list *maps, char *line)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list) * 1)))
	{
		free(line);
		return (NULL);
	}
	if (tmp)
	{
		tmp->content = ft_strdup(line);
		tmp->next = maps;
	}
	free(line);
	return (tmp);
}