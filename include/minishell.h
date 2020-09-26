#ifndef MINISHELL_H
#define MINISHELL_H

#include "parsing.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

#define FALSE 1
#define TRUE 0

typedef	struct		s_redir
{
	char                *str;
    int                 type;
}					t_redir;

typedef struct  s_pars
{
    t_list     *in;
    t_list     *out; 
}               t_pars;


typedef struct      s_sh
{
    char            *path;
    char            **cmd;
    int             begin_lencmd;
    int             continue_cmd;
    int             nb_cmd;
    int             is_pipe;
    int             last_pipe;
    int             fdd;
    int             fd[2];
    pid_t           pid;
    t_pars          pars;
}                   t_sh;

t_list	*g_env;
t_list	*g_export;
char    **g_env_tab;
pid_t   g_pid;
int     g_status;

void                free_all(char **env, t_sh *sh);
void                free_array(char **array);
char                *ft_get_var(t_list *list, char *var);
int                 ft_surch_var(t_list *list, char *var);
int                 ft_get_path_absolute(t_list *list, t_sh *sh);
int                 ft_is_bultin(char *cmd);
void                ft_exec_builtin(t_list *list, char **cmd_builtin);
int                 ft_cd(t_list *list, char **cmd_builtin);
int                 ft_pwd(char **cmd_builtin);
int                 ft_echo(char **cmd_builtin);
int                 ft_exit(char **cmd_builtin);
int                 ft_env(char **cmd_builtin);
int                 ft_export(char **cmd_builtin);
int                 ft_error(char *cmd_name, char *arg, char *msg);
int                 ft_error_var_export(char *cmd);
int                 ft_unset(char **cmd_builtin);
int                 ft_strerror(char *msg);
int                 ft_str_error(char *cmd_name, char *arg, char *msg);
int                 ft_lentab(char **tab);
int                 ft_rank_export(t_list *export);
void                ft_lstprint_rank_export(t_list *lst);
void                ft_init(t_sh *sh, char **envp);
void                ft_insensitive_typing(int nb);
void                ft_deal_nothing(int nb);
int		            ft_len_cmd(char *line, int i, int begin);
int		            ft_isspace(char *line, int index);
int 		        ft_exec_pipe(t_sh *sh, char **cmd);
int                 ft_deal_redir(t_sh *sh);
void                ft_replace(t_list *export, char *newcmd, char *var);
int     ft_count_cmd(char *line);
void    ft_initpars(t_sh *shell);
void    free_array(char **array);
void    ft_cleanbackslash(char *str);
void    ft_cleanquote(char *str);
char    *ft_getactivvar(char *src);
char    *ft_strswap(char *src, char *ad, int i, int jmp);
int     ft_openquote(char *src);
int     ft_is_builtin(char *cmd);
void    ft_initpars(t_sh *shell);
char	*ft_strvardup(const char *s, int n);
int     ft_activslash(char *src, int i);
int     ft_passsinglequote(char *str);
int     ft_passdblquote(char *str);
int     ft_checktocken(char *str, int i, char c);
int     ft_check_nbcmd(char *line, char c);
void    ft_spaceinsglquote(char *str);
void    ft_spaceindblquote(char *str);
int     ft_spaceredirection(char *str);
int     ft_addspace(char *str);
char    *ft_parscmd(char *str);
char    *ft_isolateredirection(char *str, int nb_redir);
char    *ft_startisolation(char *str, char *p, int i, int l);
char	*ft_vardup(const char *s, int n);
char    *ft_cpydblquote(char *src, char *dest, int i);
char    *ft_cpysignlequote(char *src, char *dest, int i);
void    ft_spaceindblquote(char *str);
void    ft_spaceinsglquote(char *str);
int     ft_passdblquote(char *str);
int     ft_passsinglequote(char *str);
int     ft_spaceredirection(char *str);
void    ft_addback_space(char **cmd);
void    ft_printcmd(char **cmd);
char    **ft_cleancmd(char **cmd, t_sh *shell);
int     checksorti(char *line);
int     checkentre(char *line);
t_redir	creat_redir(char *str, int type);
t_redir	*malloc_redir(char *str, int type);
void	destroy_redir(t_redir to_destroy);
void	free_redir(t_redir *to_free);
void    lst_free_redir(void *to_free);
char	**ft_array_delone(char **tab, int nb);
size_t  ft_array_len(char **tab);
char    **ft_parse(char *line, t_sh *sh);
int     ft_openquote(char *src);
char    *ft_get_var_parsing(t_list *list, char *var);
void	ft_printredir(t_list *lst);
void    ft_delate_quote(char **cmd);

#endif