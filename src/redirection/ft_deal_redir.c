#include "../../include/minishell.h"

int     ft_redir(char *file, int j, char chevron)
{
    int fd;

    fd = -1;
    if (chevron == '>')
    {
        if (j == 1)
            fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (j == 2)
            fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (fd < 0)
            return (ft_strerror(file));
        dup2(fd, 1);
        close(fd);
    }
    else if (chevron == '<')
    {
        if ((fd = open(file, O_RDONLY)) < 0)
            return (ft_strerror(file));
        dup2(fd, 0);
        close(fd);
    }
    return (0);
}

int    ft_deal_redir(t_sh *sh)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    tmp = NULL;
    if (!sh->pars->out || !sh->pars->in)
        return(0);
    while (sh->cmd[i])
    {
        j = 0;
        while (sh->cmd[i][j])
        {
            if(sh->cmd[i][j] == '>' || sh->cmd[i][j] == '<')
            {
                while(sh->cmd[i][j] == '>' || sh->cmd[i][j] == '<')
                    j++;
                tmp = ft_substr(sh->cmd[i], j, ft_strlen(sh->cmd[i]) - j);
                ft_redir(tmp, j, sh->cmd[i][0]);
                free(sh->cmd[i]);
                sh->cmd[i] = NULL;
                free(tmp);
                tmp= NULL;
                break ;
            }
            j++;
        }
        i++;
    }
    return(0);
}
