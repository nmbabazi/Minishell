#include "../include/minishell.h"

int    ft_strerror(char *msg)
{
    ft_putstr_fd(msg, 2);
    ft_putstr_fd(" ", 2);
   // ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    return (errno);
}