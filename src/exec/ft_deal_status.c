#include "../../include/minishell.h"

void	ft_deal_status(int status)
{
	g_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
		g_status = WSTOPSIG(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status);
	if (WTERMSIG(status) == 3)
		g_status = 131;
}
