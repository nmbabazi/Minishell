/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 16:24:48 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_endstring(char *line, int i)
{
	while (line[i])
		i++;
	return (i);
}

void	ft_cmd(char *cmd, t_sh *sh)
{
	if ((sh->cmd = ft_parse(cmd, sh)) == NULL)
	{
		g_error_parsing = 1;
		free(cmd);
		return ;
	}
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("");
	else if (sh->is_pipe == 1 || sh->last_pipe == 1)
		ft_exec_pipe(sh);
	else if (sh->is_pipe == 0 && sh->last_pipe == 0)
		exec_cmd(sh);
	free_array(sh->cmd);
	ft_lstclear(&sh->pars.out, lst_free_redir);
	ft_lstclear(&sh->pars.in, lst_free_redir);
	free(cmd);
	cmd = NULL;
}
