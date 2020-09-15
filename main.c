#include "include/minishell.h"

/*
// A faire :
// - Gerer >test
//
*/

static void	exec_cmd(t_sh *sh)
{
	g_pid = 0;
	int		status = 0;

	g_pid = fork();
	if (g_pid < 0)
		ft_strerror("fork : ");
	else if (g_pid > 0)
	{
		waitpid(g_pid, &status, 0);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		kill(g_pid, SIGTERM);
	}
	else
	{
		if (sh->pars.out || sh->pars.in)
			ft_deal_redir(sh);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		else if (sh->cmd[0])
		{
			ft_get_path_absolute(g_env, sh);
			if (execve(sh->cmd[0], sh->cmd, g_env_tab) == -1)
				exit(ft_strerror("minishell : "));
		}
		exit(EXIT_FAILURE);
	}
}

void	ft_cmd(char *cmd, t_sh *sh, char **envp)
{
	if ((sh->cmd = ft_parse(cmd, sh)) == NULL)
	{
		free(cmd);
		return ;
	}
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("Command not found\n");
	else if(sh->is_pipe == 1 || sh->last_pipe == 1)
	{
		if (sh->cmd[0])
			ft_get_path_absolute(g_env, sh);
		ft_exec_pipe(sh, sh->cmd, envp);
	}
	else 
		exec_cmd(sh);
	free_array(sh->cmd);
	ft_lstclear(&sh->pars.out, lst_free_redir);
	ft_lstclear(&sh->pars.in, lst_free_redir);
	free(cmd);
	cmd = NULL;
}

int		ft_semilicon(char *line, int i, t_sh *sh, char **envp)
{
	int len;
	char *tmp;

	len  = 0;
	tmp = NULL;
	sh->begin_lencmd = ft_isspace(line, sh->begin_lencmd);
	len = ft_len_cmd(line, i, sh->begin_lencmd);
	tmp = ft_substr(line, sh->begin_lencmd, len);
	if (ft_openquote(tmp) == 0)
		ft_cmd(tmp, sh, envp);
	else if (ft_openquote(tmp) == 1 && line[i + 1] != '\0')
	{
		i++;
		i = ft_isspace(line, i);
		free(tmp);
		tmp = ft_substr(line, sh->begin_lencmd, (i + 1) - sh->begin_lencmd);
		if (ft_openquote(tmp) == 1)
		{
			free(tmp);
			tmp = NULL;
			ft_strerror("minishell : erreur de syntaxe");
			return (-1);
		}
		else
			ft_cmd(tmp, sh, envp);
	}
	return (i);
}

void	ft_get_cmd(char *line, t_sh *sh, char **envp)
{
	int i;

	i = 0;
	sh->fdd = 0;
	sh->begin_lencmd = 0;
	i = ft_isspace(line, i);
	if (ft_strchr(line, ';') == NULL && ft_strchr(line, '|') == NULL)
			ft_cmd(ft_strdup(line), sh, envp);
	else if (line[i] == ';' || line[i] == '|' || ft_check_nbcmd(line) != 1)
		ft_strerror("minishell : erreur de syntaxe.");
	else
	{

		while (line[i])
		{
			sh->last_pipe = 0;
			if ((line[i] == ';' && line[i - 1] == '\\') ||
			(line[i] == '|' && line[i - 1] == '\\'))
				i++;
			if (line[i] == ';' || (line[i + 1] == '\0' && line[i] != ';') ||
			line[i] == '|')
			{
				if (line[i + 1] == '\0' && line[i] == '|')
				{
					ft_strerror("minishell : erreur de syntaxe");
					break ;
				}
				if (line[i] == '|')
					sh->is_pipe = 1;
				if (line[i] != '|' && sh->is_pipe == 1)
				{
					sh->is_pipe = 0;
					sh->last_pipe = 1;
				}
				i = ft_semilicon(line, i, sh, envp);
				if (i == -1)
					break ;
				sh->begin_lencmd = i + 1;
			}
			i++;
		}
	}
}

int     main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
    char    *line;
    int     ret;
    t_sh    sh;
	
	ft_init(&sh, envp);
	ft_rank_export(g_export);
    line = NULL;
    ret = 0;
	if(ac == 3 && !ft_strcmp(av[1], "-c"))
	{
		ft_get_cmd(av[2], &sh, envp);
	}
	else 
	{
		ft_putstr_fd("$> ", 2);
		signal(SIGQUIT, ft_deal_nothing);
		signal(SIGINT, ft_insensitive_typing);
		while ((ret = get_next_line(1, &line)) > 0)
		{
			// ft_verif erreur : \, quote...
			sh.is_pipe= 0;
			ft_get_cmd(line, &sh, envp);
			free(line);
			line = NULL;
			ft_putstr_fd("$> ", 2);
		}
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(errno);
		}
		if (ret == -1)
			exit(errno);
		free(line);
		line = NULL;
	}
    free_all(envp, &sh);
    return (0);
}