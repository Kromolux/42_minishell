/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:16:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/03 11:45:26 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# define PROMPT "MINISHELL: "
# define EXPORT "declare -x "
# define FILE_RIGHTS 0744
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# endif

typedef struct s_redirect {
	int					in;
	int					out;
	int					err;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_command {
	int					pid;
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
	struct sigaction	response;
}				t_data;

typedef struct s_parse {
	int					i;
	int					start;
	int					i_string;
	char				*string[128];
}				t_parse;

int				g_ctrl_c;

//ft_signal_handler.c
void			ft_interactive_sigint(int sign);
void			ft_bash_sigint(int sign);

//ft_minishell.c
int				ft_cycle_cmd(t_data *data);

//ft_error0.c
int				ft_print_error(t_command *cmd, int errnum, char *filename);
int				ft_error_codes(t_command *cmd);

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
void			ft_write_fd(int fd, char *s);

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
int				ft_check_cmd(t_command **cmd, int *argc, char *token);

//ft_parser1.c
void			ft_inside_d_quote(t_parse *check, char *input, t_data *data);
void			ft_inside_s_quote(t_parse *check, char *input);
void			ft_found_dollar(t_parse *check, char *input, t_data *data);
char			*ft_prepare_output(t_parse *check);
char			*ft_get_next_token(char **input, t_data *data);

//ft_env0.c
t_envp			*ft_copy_envp(char **envp);
t_envp			*ft_lstnew(char *content);
t_envp			*ft_lstlast(t_envp *lst);
void			ft_lstadd_back(t_envp **lst, t_envp *new);
void			ft_delete_list(t_envp **lst);
char			*ft_getenv(char *var, t_envp *envp_list);

//ft_env1.c
int				ft_env(t_data *data, t_command *cmd);
char			*ft_get_var(char *s);
int				ft_str_var_cmp(char *var_name, char *var_elem);
t_envp			*ft_get_envp_element(t_envp *lst, char *var);
int				ft_count_of_envp(t_envp *envp);

//ft_commands0.c
t_command		*ft_create_cmd_elem(void);
void			ft_delete_cmd(t_command **commands);
t_command 		*ft_create_cmd(char *cmd);
void			ft_print_commands(t_command *commands);
int				ft_build_in_exe(t_command *cmd, t_data *data);

//ft_export0.c
int				ft_export(t_data *data, t_command *cmd);
int				ft_check_validity(char *argv);
void			ft_var_printing(t_data *data);
t_envp			*ft_copy_envp_list(t_envp *envp);
void			ft_add_quotes(t_envp *envp);

//ft_export1.c
void			ft_sort_list(t_envp **envp);
void			ft_swap(t_envp **first, t_envp *swap_a);
void			ft_change_envp(t_data *data, char *var);

//ft_unset.c
int				ft_unset(t_data *data, t_command *cmd);
void			ft_delete_envp_elem(t_envp **first, t_envp *to_del);

//ft_pwd.c
int				ft_pwd(t_command *cmd);

//ft_echo.c
int				ft_echo(t_command *cmd);
int				ft_valid_option(char *input);

//ft_cd.c
int				ft_cd(t_data *data, t_command *cmd);

//ft_pipe.c
int				ft_create_pipe(t_command *cmd);
int				ft_connect_pipe(t_command *cmd);
int				ft_close_pipe(t_command *cmd);

//ft_executable.c
int				ft_do_execve(t_command *cmd, t_data *data);
char			*ft_check_path(char *cmd, char **paths);
char			**ft_create_envp_array(t_envp *envp);

//ft_split.c
char			**ft_split(char const *s, const char c);
size_t			ft_words_in_str(char const *s, const char c);
void			ft_free_char_array(char **array);

//ft_redirect.c
void			ft_redirect_in(t_command *cmd, char *filename);
void			ft_redirect_out(t_command *cmd, char *filename);
void			ft_redirect_out_out(t_command *cmd, char *filename);
void			ft_redirect_in_in(t_command *cmd, char *end_term);
void			ft_heredoc(int fd_out, char *end_term);

//ft_get_next_line.c
char			*ft_get_next_line(int fd);

#endif
