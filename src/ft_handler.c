#include "../include/minishell.h"

// Deal (ctr \)
void	ft_deal_nothing(int nb)
{
	(void)nb;

	if (g_fork == 0)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
	}
	else
	{
		ft_putstr("Quit (core dumped)\n");
		g_status = 131;
	}
	return ;
}

// Deal (ctr C)
void	ft_insensitive_typing(int nb) 
{
	(void)nb;
	signal(SIGINT, ft_insensitive_typing);
	ft_putstr("\n");
	ft_putstr("$> ");
	g_status = 130;
}