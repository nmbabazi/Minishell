#include "../include/minishell.h"

void	ft_cmd(char *cmd, t_sh *sh)
{
	if ((sh->cmd = ft_parse(cmd, sh)) == NULL)
	{
		free(cmd);
		return ;
	}
	if (sh->cmd[0] && ft_strcmp(sh->cmd[0], "export") == 0)
		sh->is_export = 1;
	if (sh->cmd[0] == NULL && !sh->pars.out)
		ft_putstr("");
	else if((sh->is_pipe == 1 || sh->last_pipe == 1) && sh->is_export == 0)
	{
		if (sh->cmd[0])
			ft_get_path_absolute(g_env, sh);
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

int     ft_error_pipe(char *line, int i)
{
    if (line[i + 1] == '\0' && line[i] == '|')
    {
        ft_error("minishell : erreur de syntaxe\n", NULL, NULL);
		g_status = 1;
        return (1);
    }
    return (0);
}

void    ft_split_cmd(char *line, int i, t_sh *sh)
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
            if (ft_error_pipe(line, i) == 1)
                break ;
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
}

void	ft_get_cmd(char *line, t_sh *sh)
{
	int i;

	g_fork = 0;
	i = 0;
	sh->fdd = 0;
	sh->begin_lencmd = 0;
	sh->is_pipe = 0;
	sh->last_pipe = 0;
	sh->is_export = 0;
	i = ft_isspace(line, i);
	if (ft_strchr(line, ';') == NULL && ft_strchr(line, '|') == NULL)
		ft_cmd(ft_strdup(line), sh);
	else if (line[i] == ';' || line[i] == '|' || ft_openquote(line) == 1 ||
			ft_check_nbcmd(line, ';') != 1 ||
			ft_check_nbcmd(line, '|') != 1)
	{
		ft_error("minishell: syntax error near unexpected token ",
		"« ; » ou « | »", 
		"\n");
		g_status = 2;
	}
	else
	{
        ft_split_cmd(line, i, sh);
		if (sh->nb_cmd == 0 && ft_openquote(line))
		{
			ft_strerror("minishell : syntax error");
			g_status = 1;
		}
	}
}