/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/12 19:19:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir		creat_redir(char *str, int type)
{
	t_redir result;

	result.str = ft_strdup(str);
	result.type = type;
	return (result);
}

t_redir		*malloc_redir(char *str, int type)
{
	t_redir *result;

	if (!(result = malloc(sizeof(t_redir))))
		return (NULL);
	*result = creat_redir(str, type);
	return (result);
}

void	destroy_redir(t_redir to_destroy)
{
	free(to_destroy.str);
}

void	free_redir(t_redir *to_free)
{
	destroy_redir(*to_free);
	free(to_free);
}

void lst_free_redir(void *to_free)
{
	free_redir(to_free);
}
