/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:16:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/25 20:46:56 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define PROMPT "MINISHELL: "
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif
# ifndef PATH
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
#endif

typedef struct s_command {
	char				*cmd;
	char				*argv[128];
	struct s_command	*next;
}				t_command;

typedef struct s_envp {
	char				*var;
	struct s_envp		*next;
}				t_envp;

void			ft_pwd(void);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
void			ft_env(t_envp *envp_list);
t_command 		*ft_create_cmd(char *cmd);
int				ft_quote(char *cmd);
size_t			ft_strlen(const char *s);
char			*ft_skip_whitespaces(const char *str);
int				ft_end_of_token(char *s);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_copy(char *dst, char *src, size_t size);
char			*ft_get_substring(char const *s, size_t start, size_t len);
char			*ft_string_dup(const char *s);
size_t			ft_get_int_len(long n, int sign);
char			*ft_int_to_string(long n);
int				ft_print_error(int errnum, char *cmd);
int				ft_equal(char *s);
void			ft_delete_cmd(t_command *commands);
void			ft_print_commands(t_command *commands);
size_t			ft_count_of_in_str(const char *s, const char c);
char			*ft_remo_dq(char *s);

//ft_env.c
t_envp			*ft_copy_envp(char **envp);
t_envp			*ft_lstnew(char *content);
t_envp			*ft_lstlast(t_envp *lst);
void			ft_lstadd_back(t_envp **lst, t_envp *new);
void			ft_delete_list(t_envp **lst);
char			*ft_getenv(char *var, t_envp *envp_list);

#endif
