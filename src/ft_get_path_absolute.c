#include "../include/minishell.h"

int     ft_verif_path(char *bin)
{
    struct stat mystat;

    errno = 0;
    stat(bin, &mystat);
    if(errno)
        return (FALSE);
	if ((mystat.st_mode & S_IFMT) == S_IFDIR)
	{
		errno = EISDIR;
		return (FALSE);
	}
    return (TRUE);
}

void    ft_get_path_absolute(t_list *list, t_sh *sh)
{
    char **path_split;
    char *bin;
    int i;

    path_split = NULL;
    bin = NULL;
    i = 0;
    sh->path = ft_get_var(g_env,"PATH=");
    if (sh->cmd[0][0] != '/' || strncmp(sh->cmd[0], "./", 2) != 0)
    {
        path_split = ft_split(sh->path, ':');
        while(path_split[i])
        {
            bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(sh->cmd[0]) + 1));
             if (bin == NULL)
                break ;
            ft_strcat(bin, path_split[i]);
            ft_strcat(bin, "/");
            ft_strcat(bin, sh->cmd[0]);
            if (ft_verif_path(bin) == 0)
            {
                free(sh->cmd[0]);
                sh->cmd[0] = bin;
                break ;
            }
            free(bin);
            bin = NULL;
            i++;
        }
        free_array(path_split);
        if (sh->path)
        {
            free(sh->path);
            sh->path = NULL;
        }
    }
}