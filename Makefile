# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 09:14:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/03/29 09:31:38 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

CC			:=	gcc
HEADERFILE	:=	minishell.h

SRC			:=	ft_minishell.c \
				ft_error0.c \
				ft_utils0.c \
				ft_utils1.c \
				ft_utils2.c \
				ft_parser0.c \
				ft_parser1.c \
				ft_commands0.c \
				ft_env0.c \
				ft_env1.c \
				ft_export0.c \
				ft_export1.c \
				ft_unset.c \
				ft_pwd.c \
				ft_echo.c \
				ft_cd.c \
				ft_executable.c \
				ft_split.c \
				ft_pipe.c

OBJ			:=	$(SRC:%.c=%.o)

CFLAGS		:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L/usr/include -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADERFILE)

.PHONY: clean fclean re