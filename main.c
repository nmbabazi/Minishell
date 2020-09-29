#include "include/minishell.h"

/* A faire
//echo salut || echo ca va
*/



int     main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
    char    *line;
    int     ret;
    t_sh    sh;
	
	ft_init(&sh, envp);
	ft_rank_export(g_export);
    line = NULL;
    ret = 0;
	signal(SIGQUIT, ft_deal_nothing);
	signal(SIGINT, ft_insensitive_typing);
	if(ac == 3 && !ft_strcmp(av[1], "-c"))
	{
		ft_get_cmd(av[2], &sh);
	}
	else 
	{
		ft_putstr_fd("$> ", 2);

		while ((ret = get_next_line(1, &line)) > 0)
		{
			
			sh.is_pipe= 0;
			ft_get_cmd(line, &sh);
			free(line);
			line = NULL;
			ft_putstr_fd("$> ", 2);
		}
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(errno);
		}
		if (ret == -1)
			exit(errno);
		free(line);
		line = NULL;
	}
    free_all(envp, &sh);
    return (g_status);
}