#include "include/minishell.h"

/* A faire
//
// cd ""
// echo || echo
// $> pwd | cat -e
//home/user42/Documents/mini_fusion$
//$> unset PATH
//$> export
// echo -> si tab gere espace
// exit + code
// msg erreur avec "succes"
*/

int		exec_cmd(t_sh *sh)
{
	int	status;
	
	g_pid = 0;
	status = g_status;
	g_pid = fork();
	if (g_pid < 0)
		ft_strerror("fork : ");
	else if (g_pid > 0)
	{
		if (waitpid(g_pid, &status, 0) == -1)
			return(ft_str_error("minishell: ", "wait", NULL));
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		status = WEXITSTATUS(status);
		printf("status = %d\n", status);
		g_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_status = WTERMSIG(status);
		kill(g_pid, SIGTERM);
	}
	else
	{
		if (sh->pars.out || sh->pars.in)
			if(ft_deal_redir(sh) != 0)
				exit(g_status);
		if (sh->cmd[0] && ft_is_bultin(sh->cmd[0]) == TRUE)
			ft_exec_builtin(g_env, sh->cmd);
		else if (sh->cmd[0])
		{
			ft_get_path_absolute(g_env, sh);
			if (execve(sh->cmd[0], sh->cmd, g_env_tab) == -1)
			{
				ft_str_error(sh->cmd[0], " : commande introuvable\n", NULL);
				g_status = 127;
				exit(g_status);
			}
		}
		exit(g_status);
	}
}

void	ft_cmd(char *cmd, t_sh *sh)
{
	if ((sh->cmd = ft_parse(cmd, sh)) == NULL)
	{
		free(cmd);
		return ;
	}
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("\n");
	else if(sh->is_pipe == 1 || sh->last_pipe == 1)
	{
		if (sh->cmd[0])
			ft_get_path_absolute(g_env, sh);
		ft_exec_pipe(sh, sh->cmd);
	}
	else 
		exec_cmd(sh);
	free_array(sh->cmd);
	ft_lstclear(&sh->pars.out, lst_free_redir);
	ft_lstclear(&sh->pars.in, lst_free_redir);
	free(cmd);
	cmd = NULL;
}

int		ft_separate(char *line, int i, t_sh *sh)
{
	int 	len;
	char	*tmp;

	len  = 0;
	sh->continue_cmd = 0;
	sh->begin_lencmd = ft_isspace(line, sh->begin_lencmd);
	len = ft_len_cmd(line, i, sh->begin_lencmd);
	tmp = ft_substr(line, sh->begin_lencmd, len);
	
	if (ft_openquote(tmp) == 0)
	{
		sh->nb_cmd++;
		ft_cmd(tmp, sh);
	}
	else if (ft_openquote(tmp) == 1)
	{
		sh->continue_cmd = 1;
		free(tmp);
		tmp = NULL;
		sh->is_pipe = 0;
	}
	return (i);
}

void	ft_get_cmd(char *line, t_sh *sh)
{
	int i;

	i = 0;
	sh->fdd = 0;
	sh->begin_lencmd = 0;
	i = ft_isspace(line, i);
	if (ft_strchr(line, ';') == NULL && ft_strchr(line, '|') == NULL)
			ft_cmd(ft_strdup(line), sh);
	else if (line[i] == ';' || line[i] == '|' ||
			ft_check_nbcmd(line, ';') != 1 ||
			ft_check_nbcmd(line, '|') != 1)
		ft_error("minishell: erreur de syntaxe près du symbole inattendu ",
		"« ; » ou « | »", 
    	"\n");
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
				i = ft_separate(line, i, sh);
				if (sh->continue_cmd == 0)
					sh->begin_lencmd = i + 1;
			}
			i++;
		}
		if (sh->nb_cmd == 0 && ft_openquote(line))
			ft_strerror("minishell : erreur de syntaxe");
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
		ft_get_cmd(av[2], &sh);
	}
	else 
	{
		ft_putstr_fd("$> ", 2);
		signal(SIGQUIT, ft_deal_nothing);
		signal(SIGINT, ft_insensitive_typing);
		while ((ret = get_next_line(1, &line)) > 0)
		{
			sh.is_pipe= 0;
			ft_get_cmd(line, &sh);
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
    return (g_status);
}