# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 09:14:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/04/09 20:47:56 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#valgrind --leak-check=full --show-leak-kinds=all --ignore-fn=readline ./minishell
#valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

NAME		:=	minishell

CC			:=	gcc
HEADERFILE	:=	minishell.h

SRC			:=	ft_minishell.c \
				ft_error0.c \
				ft_error1.c \
				ft_error2.c \
				ft_utils0.c \
				ft_utils1.c \
				ft_utils2.c \
				ft_utils3.c \
				ft_utils4.c \
				ft_utils5.c \
				ft_parser0.c \
				ft_parser1.c \
				ft_parser2.c \
				ft_parser3.c \
				ft_parser4.c \
				ft_parser5.c \
				ft_commands0.c \
				ft_commands1.c \
				ft_env0.c \
				ft_env1.c \
				ft_env2.c \
				ft_export0.c \
				ft_export1.c \
				ft_unset.c \
				ft_pwd.c \
				ft_echo.c \
				ft_cd.c \
				ft_executable.c \
				ft_split.c \
				ft_pipe.c \
				ft_redirect0.c \
				ft_redirect1.c \
				ft_redirect2.c \
				ft_get_next_line.c \
				ft_signals.c \
				ft_signal_handler.c \
				ft_exit.c \
				ft_wildcard0.c \
				ft_wildcard1.c

OBJ			:=	$(SRC:%.c=%.o)

CFLAGS		:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/local/opt/readline/include/ -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) $(HEADERFILE)

val:
	valgrind --leak-check=full --trace-children=yes ./minishell

.PHONY: clean fclean re