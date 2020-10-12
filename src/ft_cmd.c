/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/12 15:20:11 by user42           ###   ########.fr       */
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
	if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "export") == 0)
		sh->is_export = 1;
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("");
	else if ((sh->is_pipe == 1 || sh->last_pipe == 1) && sh->is_export == 0)
	{
		if (sh->cmd[0])
			ft_get_path_absolute(sh);
		ft_exec_pipe(sh, sh->cmd);
	}
	else if ((sh->is_pipe == 0 && sh->last_pipe == 0))
		exec_cmd(sh);
	free_array(sh->cmd);
	ft_lstclear(&sh->pars.out, lst_free_redir);
	ft_lstclear(&sh->pars.in, lst_free_redir);
	free(cmd);
	cmd = NULL;
}
