#include "../include/minishell.h"

int     ft_lentab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}
