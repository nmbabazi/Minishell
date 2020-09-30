#include "../../include/minishell.h"

void     ft_verif_permission(char *cmd)
{
    struct stat permstat;

    errno = 0;
	if (ft_strncmp(cmd, "./", 2) != 0)
		return ;
    stat(cmd, &permstat);
    if(errno)
        return ;
	if ((permstat.st_mode & S_IFMT) == S_IFREG)
	{
		if (!((permstat.st_mode & S_IFMT) == S_IXUSR))
		{
			ft_error("minishell: ", cmd, ": Permission denied\n");
			exit(126);
		}
	}
}
