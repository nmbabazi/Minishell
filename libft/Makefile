# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 10:39:20 by dmontgen          #+#    #+#              #
#    Updated: 2020/09/15 18:42:18 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_tab_to_list.c \
			ft_str_to_list.c \
			ft_lstadd_back.c \
			ft_lstclear.c \
			ft_lstprint.c \
			ft_lstdelone.c \
			ft_freestr.c \
			ft_strndup.c \
			ft_add_link.c \
			ft_lstnew.c \
			ft_lstlen.c \
			ft_lststring_to_tab.c \
			get_next_line.c \

OBJ		=	$(SRCS:.c=.o)

all		:	$(NAME)

%.o	: %.c
	gcc -o $@ -c $< 

$(NAME) :
	gcc -c $(CFLAGS) $(SRCS)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean	:		
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re : fclean all
