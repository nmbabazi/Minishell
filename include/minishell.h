/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 17:37:49 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/10/19 18:35:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>

# define FALSE 1
# define TRUE 0

typedef	struct		s_redir
{
	char			*str;
	int				type;
}					t_redir;

typedef	struct		s_pars
{
	t_list			*in;
	t_list			*out;
}					t_pars;

typedef struct		s_sh
{
	char			*path;
	char			**cmd;
	int				begin_lencmd;
	int				continue_cmd;
	int				nb_cmd;
	int				is_pipe;
	int				last_pipe;
	int				is_export;
	int				fdd;
	int				fd[2];
	t_pars			pars;
}					t_sh;

t_list				*g_env;
t_list				*g_export;
char				**g_env_tab;
pid_t				g_pid;
int					g_status;
int					g_error_parsing;
int					g_fork;

void				free_all(void);
void				free_array(char **array);
char				*ft_get_var(t_list *list, char *var);
int					ft_surch_var(t_list *list, char *var);
int					ft_get_path_absolute(t_sh *sh);
void				ft_get_cmd(char *line, t_sh *sh);
void				ft_cmd(char *cmd, t_sh *sh);
void				ft_init_get_cmd(t_sh *sh);
int					exec_cmd(t_sh *sh);
void				ft_deal_status(int status);
void				ft_verif_permission(char *cmd);
int					ft_is_bultin(char *cmd);
void				ft_exec_builtin(char **cmd_builtin);
int					ft_cd(char **cmd_builtin);
int					ft_error_var_export(char *cmd);
int					ft_pwd(char **cmd_builtin);
int					ft_echo(char **cmd_builtin);
int					ft_shlvl(char **cmd_builtin);
int					ft_exit(char **cmd_builtin);
int					ft_env(char **cmd_builtin);
int					ft_export(char **cmd_builtin);
int					ft_error(char *cmd_name, char *arg, char *msg);
int					ft_error_var_export(char *cmd);
int					ft_error_pipe(char *line, int i);
int					ft_unset(char **cmd_builtin);
int					ft_str_error(char *cmd_name, char *arg, char *msg);
int					ft_lentab(char **tab);
int					ft_endstring(char *line, int i);
unsigned int		ft_len_var(char *str);
int					ft_rank_export(t_list *export);
void				ft_lstprint_rank_export(t_list *lst);
void				ft_init(t_sh *sh, char **envp);
void				ft_insensitive_typing(int nb);
void				ft_deal_nothing(int nb);
int					ft_len_cmd(char *line, int i, int begin);
void				ft_is_file(char *cmd);
int					ft_isspace(char *line, int index);
int					ft_exec_pipe(t_sh *sh, char **cmd);
int					ft_deal_redir(t_sh *sh);
void				ft_replace(t_list *export, char *newcmd, char *var);
int					ft_count_cmd(char *line);
void				ft_initpars(t_sh *shell);
void				free_array(char **array);
void				ft_cleanbackslash(char *str);
void				ft_cleanquote(char *str);
char				*ft_getactivvar(char *src);
char				*ft_strswap(char *src, char *ad, int i, int jmp);
int					ft_openquote(char *src);
int					ft_is_builtin(char *cmd);
void				ft_initpars(t_sh *shell);
char				*ft_strvardup(const char *s, int n);
int					ft_activslash(char *src, int i);
int					ft_passsinglequote(char *str);
int					ft_passdblquote(char *str);
int					ft_checktocken(char *str, int i, char c);
int					ft_check_nbcmd(char *line, char c);
void				ft_spaceinsglquote(char *str);
void				ft_spaceindblquote(char *str);
int					ft_spaceredirection(char *str);
int					ft_addspace(char *str);
char				*ft_parscmd(char *str);
char				*ft_isolateredirection(char *str, int nb_redir);
char				*ft_startisolation(char *str, char *p, int i, int l);
char				*ft_vardup(const char *s, int n);
char				*ft_cpydblquote(char *src, char *dest, int i);
char				*ft_cpysignlequote(char *src, char *dest, int i);
void				ft_spaceindblquote(char *str);
void				ft_spaceinsglquote(char *str);
int					ft_passdblquote(char *str);
int					ft_passsinglequote(char *str);
int					ft_spaceredirection(char *str);
void				ft_addback_space(char **cmd);
void				ft_printcmd(char **cmd);
char				**ft_cleancmd(char **cmd, t_sh *shell);
int					checksorti(char *line);
int					checkentre(char *line);
t_redir				creat_redir(char *str, int type);
t_redir				*malloc_redir(char *str, int type);
void				destroy_redir(t_redir to_destroy);
void				free_redir(t_redir *to_free);
void				lst_free_redir(void *to_free);
char				**ft_parse(char *line, t_sh *sh);
int					ft_openquote(char *src);
char				*ft_get_var_parsing(t_list *list, char *var);
void				ft_printredir(t_list *lst);
void				ft_delate_quote(char **cmd);
int					ft_isredirected(char **cmd);
void				ft_dell_backslash(char **cmd);
char				*ft_strcat_norm(char *dest, char *src);
char				**ft_dell_redir(char **cmd);
void				ft_array_cpy(char **new, char **tab);
void				ft_getredir(char **cmd, t_sh *sh);
void				ft_add_file(char *cmd, t_list **out, int type);
void				ft_cleanbackslash_inquote(char *str);
int					ft_escapechar_quote(char c);
int					ft_isredirection(char *str, int i);
int					ft_passdbl_insgl(char *str);
int					ft_spaceafterslash(char *str);
char				*ft_cpyvar(char *str, char *ret, int i, int l);
char				*ft_addvar(char *str, int i);
int					add_varsize(char *src, int i, int len);
int					ft_namesize(char *src);
char				*ft_cpyandclean(char *str);
char				*ft_delate_backslash(char *str);
void				ft_addback_quote(char *str);
int					ft_verifstring(char *str, int i);
int					ft_isvar(char *str, int i);
int					ft_isvarname(char c);
void				unmute_sgl_in_dbl(char *str);
void				mute_sgl_in_dbl(char *str);
int					ft_activslash_dell(char *src, int i);
void				ft_swapchar(char *str, char in, char fin);

#endif
