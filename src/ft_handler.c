#include "../include/minishell.h"

// Deal (ctr \)
void	ft_deal_nothing(int nb)
{
	(void)nb;
	if (write(STDOUT_FILENO, " \b\b \b", 5) < 0)
		return ;
	return ;
}

// Deal (ctr C)
void	ft_insensitive_typing(int nb) 
{
	(void)nb;
	signal(SIGINT, ft_insensitive_typing);
	ft_putstr("\n");
	ft_putstr("$> ");
}