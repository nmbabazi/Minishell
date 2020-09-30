NAME = minishell

SRCS = 	main.c \
		src/ft_get_var.c \
		src/ft_get_path_absolute.c \
		src/ft_get_cmd.c \
		src/ft_cmd.c \
		src/free.c \
		src/ft_error.c \
		src/ft_lentab.c \
		src/ft_init.c \
		src/ft_handler.c \
		src/builtins/ft_is_builtin.c \
		src/builtins/ft_exec_builtin.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_pwd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_exit.c \
		src/builtins/ft_env.c \
		src/builtins/ft_export.c \
		src/builtins/ft_unset.c \
		src/builtins/ft_deal_export.c \
		src/exec/exec_cmd.c \
		src/exec/ft_deal_status.c \
		src/exec/ft_verif_permission.c \
		src/exec/ft_exec_pipe.c \
		src/redirection/ft_deal_redir.c \
		src/parsing/parsing.c \
		src/parsing/startparsing.c \
		src/parsing/utiles.c \
		src/parsing/pars_dblquote.c \
		src/parsing/pars_redirection.c \
		src/parsing/redirection.c \
		src/parsing/getredirection.c \
		src/parsing/pars_singlequote.c \
		src/parsing/pars_var.c \
		src/parsing/check_redirection.c \
		src/parsing/ft_strcat_minishell.c \
		src/parsing/pars_slash.c \
		src/parsing/pars_space.c \
		src/parsing/utiles_var.c \

OBJSRCS = $(SRCS:.c=.o)

$(NAME) : $(OBJSRCS)
	@rm -rf $(NAME)
	$(MAKE) -C ./libft
	@gcc -o $(NAME) -I include/minishell.h $(OBJSRCS) ./libft/libft.a $(MLX) -Wall -Wextra -Werror -g
	#-fsanitize=address -fstack-protector
	@echo "\033[33m[Done !]"

all : $(NAME)

clean :
	rm -rf $(OBJSRCS) 
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re : fclean all