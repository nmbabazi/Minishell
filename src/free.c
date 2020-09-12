#include "../include/minishell.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
    array = NULL;
}

void    free_all(char **env, t_sh *sh)
{
   // if (env)
     //   free_array(env);
  //  if (sh->cmd)
    //    free_array(sh->cmd);
    if (g_env)
        ft_lstclear(&g_env, (void *)ft_freestr);
    if (g_export)
        ft_lstclear(&g_export, (void *)ft_freestr);
}