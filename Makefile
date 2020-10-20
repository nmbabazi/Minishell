NAME = minishell

SRCS = 	main.c \
		ft_get_var.c \
		ft_get_path_absolute.c \
		ft_get_cmd.c \
		ft_cmd.c \
		free.c \
		ft_error.c \
		ft_lentab.c \
		ft_init.c \
		ft_handler.c \
		builtins/ft_is_builtin.c \
		builtins/ft_exec_builtin.c \
		builtins/ft_cd.c \
		builtins/ft_pwd.c \
		builtins/ft_echo.c \
		builtins/ft_exit.c \
		builtins/ft_env.c \
		builtins/ft_export.c \
		builtins/ft_unset.c \
		builtins/ft_shlvl.c \
		builtins/ft_deal_export.c \
		builtins/ft_utils_builtins.c \
		exec/exec_cmd.c \
		exec/ft_deal_status.c \
		exec/ft_verif_permission.c \
		exec/ft_exec_pipe.c \
		redirection/ft_deal_redir.c \
		parsing/parsing.c \
		parsing/startparsing.c \
		parsing/utiles.c \
		parsing/pars_dblquote.c \
		parsing/pars_redirection.c \
		parsing/redirection.c \
		parsing/getredirection.c \
		parsing/pars_singlequote.c \
		parsing/pars_var.c \
		parsing/check_redirection.c \
		parsing/ft_strcat_minishell.c \
		parsing/pars_slash.c \
		parsing/pars_space.c \
		parsing/utiles_var.c \

CC = clang
SRC_DIR = src
INC_DIR = include
BUILD_DIR = obj
CFLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -g

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))


FTDIR	= libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft



all : make_ft $(NAME)

make_ft:
	@make -C $(FTDIR)


$(NAME): $(OBJ) make_ft
	$(CC) $(OBJ) $(FT_LNK) $(FT_LNKP) -o $(NAME)
	@echo "$(NAME) created"
	@echo "\033[33m[Done !]"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/builtins $(BUILD_DIR)/exec $(BUILD_DIR)/parsing $(BUILD_DIR)/redirection
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $<

clean:
	@/bin/rm -rf $(BUILD_DIR)
	@echo "Object files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Lib deleted"

re : 
	@make fclean all
	

.PHONY: all, clean, fclean, re, make_ft