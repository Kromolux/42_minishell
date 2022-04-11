# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 09:14:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/04/11 09:11:39 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#valgrind --leak-check=full --show-leak-kinds=all --ignore-fn=readline ./minishell
#valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

NAME		:=	minishell

OBJ_FOLDER	:=	objs
SRC_FOLDER	:=	srcs

CC			:=	gcc
HEADERFILE	:=	minishell.h

SRCS		:=	ft_minishell.c \
				errors/ft_error0.c \
				errors/ft_error1.c \
				errors/ft_error2.c \
				utils/ft_utils0.c \
				utils/ft_utils1.c \
				utils/ft_utils2.c \
				utils/ft_utils3.c \
				utils/ft_utils4.c \
				utils/ft_utils5.c \
				parser/ft_parser0.c \
				parser/ft_parser1.c \
				parser/ft_parser2.c \
				parser/ft_parser3.c \
				parser/ft_parser4.c \
				parser/ft_parser5.c \
				executor/ft_commands0.c \
				executor/ft_commands1.c \
				buildins/ft_env0.c \
				buildins/ft_env1.c \
				buildins/ft_env2.c \
				buildins/ft_export0.c \
				buildins/ft_export1.c \
				buildins/ft_unset.c \
				buildins/ft_pwd.c \
				buildins/ft_echo.c \
				buildins/ft_cd.c \
				executor/ft_executable.c \
				utils/ft_split.c \
				executor/ft_pipe.c \
				executor/ft_redirect0.c \
				executor/ft_redirect1.c \
				executor/ft_redirect2.c \
				utils/ft_get_next_line.c \
				signals/ft_signals.c \
				signals/ft_signal_handler.c \
				buildins/ft_exit.c \
				bonus/ft_wildcard0.c \
				bonus/ft_wildcard1.c

OBJS		:= $(SRCS:%.c=$(OBJ_FOLDER)/%.o)

CFLAGS		:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L/usr/local/opt/readline/lib -lreadline -o $(NAME)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -I/usr/local/opt/readline/include/ -o $@ $<

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -fr $(NAME)

re: fclean all

norm:
	cd srcs && norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(HEADERFILE)
	
val:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes -s ./minishell

.PHONY: clean fclean re