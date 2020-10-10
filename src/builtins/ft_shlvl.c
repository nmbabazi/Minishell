/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:53:13 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/10 12:09:13 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     ft_shlvl(char ** cmd_builtin)
{
    char *shlvl;
    int nb_shlvl;
    char *all_shlvl;

    if (cmd_builtin[1])
    {
		return (ft_error("minishell: ", cmd_builtin[1],
        ": ne peut exécuter le fichier\n"));
    }
    shlvl = ft_get_var(g_env, "SHLVL=");
    nb_shlvl = ft_atoi(shlvl);
    nb_shlvl++;
    free(shlvl);
    shlvl = ft_itoa(nb_shlvl);
    all_shlvl = ft_strjoin("SHLVL=", shlvl);
	ft_replace(g_export, all_shlvl, "SHLVL=");
	ft_replace(g_env, all_shlvl, "SHLVL=");
    free(shlvl);
    free(all_shlvl);
	free_array(g_env_tab);
	g_env_tab = ft_lststring_to_tab(g_env);
    return (0);
}