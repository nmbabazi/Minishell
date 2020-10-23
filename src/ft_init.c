/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/23 16:24:57 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_pipe(t_sh *sh)
{
	sh->is_pipe = 0;
	sh->last_pipe = 1;
}

void	ft_init_get_cmd(t_sh *sh)
{
	sh->fdd = 0;
	sh->begin_lencmd = 0;
	sh->is_pipe = 0;
	sh->last_pipe = 0;
	g_fork = 0;
	g_error_parsing = 0;
}

void	ft_init(t_sh *sh, char **envp)
{
	sh->cmd = NULL;
	sh->path = NULL;
	sh->last_pipe = 0;
	sh->is_pipe = 0;
	sh->continue_cmd = 0;
	sh->nb_cmd = 0;
	sh->ret = 0;
	sh->d = 0;
	g_fork = 0;
	g_sig = 0;
	g_env = NULL;
	g_env = ft_tab_to_list(&g_env, envp);
	g_export = ft_tab_to_list(&g_export, envp);
	g_env_tab = ft_lststring_to_tab(g_env);
	g_read = 0;
	g_str = ft_strnew(0);
}
