#include "../include/minishell.h"

int    ft_strerror(char *msg)
{
    ft_putstr_fd(msg, 2);
    ft_putstr_fd(" ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    return (errno);
}
int    ft_str_error(char *cmd_name, char *arg, char *msg)
{
    ft_putstr_fd(cmd_name, 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    //printf("errno = %d\n", errno);
    if (errno == 2 || errno == 13)
        errno = 1;
    return (errno);
}

int    ft_error(char *cmd_name, char *arg, char *msg)
{
    ft_putstr_fd(cmd_name, 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(msg, 2);
    return(1);
}