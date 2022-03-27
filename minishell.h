/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:16:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 20:45:40 by rkaufman         ###   ########.fr       */
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
# define EXPORT "declare -x "
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif
# ifndef PATH
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
#endif

typedef struct s_redirect {
	int					in;
	int					out;
	int					err;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command {
	char				*cmd;
	char				*argv[128];
	struct s_redirect	*re;
	struct s_command	*next;
}				t_command;

typedef struct s_envp {
	char				*var;
	struct s_envp		*next;
}				t_envp;

typedef struct s_data {
	struct s_envp		*envp;
	struct s_command	*c_line;
	char				*r_line;
	int					errnum;
}				t_data;

typedef struct s_parse {
	int					i;
	int					start;
	int					i_string;
	char				*string[128];
}				t_parse;


//ft_error0.c
int				ft_print_error(t_data *data);

//ft_utils0.c
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_copy(char *dst, char *src, size_t size);
char			*ft_string_dup(const char *s);
char			*ft_get_substring(char const *s, size_t start, size_t len);

//ft_utils1.c
char			*ft_int_to_string(long n);
size_t			ft_get_int_len(long n, int sign);
size_t			ft_count_of_in_str(const char *s, const char c);
char			*ft_char_in_str(const char *s, const char c);
char			*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_utils2.c
int				ft_pos_in_string(char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_remove_char(char *s, char c);

//ft_parser0.c
void			ft_parser(t_data *data);
char			*ft_skip_whitespaces(const char *str);
int				ft_len_whitespaces(const char *s);
int				ft_end_of_token(char *s, int *inside_echo);
char			*ft_check_quotes_insert_var(char *input, t_data *data);
void			ft_check_quote(char c, int *d_quote, int *s_quote);

//ft_parser1.c
void			ft_inside_d_quote(t_parse *check, char *input, t_data *data);
void			ft_inside_s_quote(t_parse *check, char *input);
void			ft_found_dollar(t_parse *check, char *input, t_data *data);
char			*ft_prepare_output(t_parse *check);

//ft_env0.c
t_envp			*ft_copy_envp(char **envp);
t_envp			*ft_lstnew(char *content);
t_envp			*ft_lstlast(t_envp *lst);
void			ft_lstadd_back(t_envp **lst, t_envp *new);
void			ft_delete_list(t_envp **lst);
char			*ft_getenv(char *var, t_envp *envp_list);

//ft_env1.c
char			*ft_get_var(char *s);
void			ft_env(t_data *data);
int				ft_str_var_cmp(char *var_name, char *var_elem);

//ft_commands0.c
t_command		*ft_create_cmd_elem(void);
void			ft_delete_cmd(t_command *commands);
t_command 		*ft_create_cmd(char *cmd);
void			ft_print_commands(t_command *commands);
int				ft_build_in_exe(t_data *data);

//ft_export.c
int				ft_export(t_data *data);
int				ft_check_validity(char *argv);
void			ft_var_printing(t_data *data);
t_envp			*ft_copy_envp_list(t_envp *envp);
void			ft_add_quotes(t_envp *envp);

//ft_unset.c
void			ft_unset(t_data *data);

//ft_pwd.c
void			ft_pwd(t_data *data);

//ft_echo.c
int				ft_echo(t_command *cmd);
int				ft_valid_option(char *input);

#endif
