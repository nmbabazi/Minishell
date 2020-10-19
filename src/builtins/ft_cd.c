/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:44:55 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/19 15:38:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_replace_pwd(char *all_pwd, char *all_old_pwd)
{
	ft_replace(g_env, all_pwd, "PWD=");
	ft_replace(g_env, all_old_pwd, "OLDPWD=");
	free_array(g_env_tab);
	g_env_tab = ft_lststring_to_tab(g_env);
	ft_replace(g_export, all_pwd, "PWD=");
	ft_replace(g_export, all_old_pwd, "OLDPWD=");
	free(all_pwd);
	free(all_old_pwd);
}

int		ft_update_pwd(void)
{
	char *old_pwd;
	char *pwd;
	char *all_pwd;
	char *all_old_pwd;

	old_pwd = NULL;
	pwd = NULL;
	all_pwd = NULL;
	all_old_pwd = NULL;
	old_pwd = ft_get_var(g_env, "PWD=");
	pwd = getcwd(pwd, 0);
	if (!old_pwd || !pwd)
	{
		ft_error("", NULL, NULL);
		free(old_pwd);
		free(pwd);
		g_status = 0;
		return (0);
	}
	all_pwd = ft_strjoin("PWD=", pwd);
	all_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	ft_replace_pwd(all_pwd, all_old_pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

int		ft_home(void)
{
	char *home;

	if (!(home = ft_get_var(g_env, "HOME=")))
	{
		if (g_pid > 0)
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return (1);
	}
	if ((chdir(home)) == -1)
		return (ft_str_error("home: home ", NULL, NULL));
	free(home);
	return (0);
}

int		ft_error_chdir(char **cmd_builtin)
{
	if (g_pid == 0)
		ft_str_error("minishell: cd: ", cmd_builtin[1], ": ");
	g_status = 1;
	return (0);
}

int		ft_cd(char **cmd_builtin)
{
	int nb;

	nb = ft_lentab(cmd_builtin);
	if (nb == 1)
		g_status = ft_home();
	else if (nb == 2)
	{
		if (cmd_builtin[1][0] == '\0')
			return (0);
		else if (cmd_builtin[1][0] == '~')
			g_status = ft_home();
		else if (chdir(cmd_builtin[1]) == -1)
			return (ft_error_chdir(cmd_builtin));
	}
	else if (nb > 2)
	{
		if (g_pid > 0)
			ft_error("minishell: cd: ", NULL,
				"too many arguments\n");
		g_status = 1;
		return (0);
	}
	if (g_pid > 0)
		ft_update_pwd();
	return (0);
}
