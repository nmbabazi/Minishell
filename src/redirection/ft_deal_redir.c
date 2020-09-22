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
            return (ft_str_error("minishell: ", file, ": "));
        dup2(fd, 1);
        close(fd);
    }
    else if (chevron == '<')
    {
        if ((fd = open(file, O_RDONLY)) < 0)
            return (ft_str_error("minishell: ", file, ": "));
        dup2(fd, 0);
        close(fd);
    }
    return (0);
}

int    ft_deal_redir(t_sh *sh)
{
    t_list *iterator;
    t_redir *deal_redir;

    iterator = sh->pars.out;
    while(iterator)
    {
        deal_redir = iterator->content;
        if (ft_redir(deal_redir->str, deal_redir->type, '>') != 0)
            return (-1);
        iterator = iterator->next;
    }
    iterator = sh->pars.in;
    while(iterator)
    {
        deal_redir = iterator->content;
        if(ft_redir(deal_redir->str, deal_redir->type, '<') != 0)
            return (-1);
        iterator = iterator->next;
    }
    return(0);
}
