#include "../../include/minishell.h"

int     ft_redir(char *file, int j, char chevron)
{
    int fd;

    fd = -1;
    //printf("putstr = \n");
   // fflush(STDOUT_FILENO);
   // ft_putstr(file);
   // printf("\nfile = -%s-\n", file);
   // printf("type = %d\n", j);
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
    t_redir *deal_redir;

    i = 0;
    j = 0;
    tmp = NULL;
    printf("oooooooooooooooooook\n");
    //if (!sh->pars.out || !sh->pars.in)
    //    return(0);

    if (sh->pars.out)
    {
        while(sh->pars.out)
        {
            deal_redir = sh->pars.out->content;
            ft_redir(deal_redir->str, deal_redir->type, '>');
            sh->pars.out = sh->pars.out->next;
        }
    }
    if (sh->pars.in)
    {
        while(sh->pars.in)
        {
            deal_redir = sh->pars.in->content;
            ft_redir(deal_redir->str, deal_redir->type, '<');
            sh->pars.in = sh->pars.in->next;
        }
    }
  /*
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
    }*/
    return(0);
}
