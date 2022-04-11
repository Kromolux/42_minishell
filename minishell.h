/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:16:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/11 09:49:34 by rkaufman         ###   ########.fr       */
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
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# define PROMPT "MINISHELL: "
# define EXPORT "declare -x "
# define FILE_RIGHTS 0664
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# endif

typedef enum e_return {
	RETURN_ERROR = -1,
	RETURN_SUCCESS = 0,
	RETURN_FALSE = 1,
	RETURN_TRUE = 2,
	RETURN_EXIT = 3
}			t_return;

typedef enum e_err_handl {
	ERR_NOT_VALID = 255,
	ERR_NUMERIC,
	ERR_TOO_ARG,
	ERR_SYNTAX,
	ERR_CMD_NOT,
	ERR_CD_FOLDER,
	ERR_FD,
	ERR_FILE
}			t_err_handl;

typedef struct s_re {
	char				*direct;
	char				*file;
	struct s_re			*next;
}				t_re;

typedef struct s_fd {
	int					in;
	int					out;
	int					err;
}				t_fd;

typedef struct s_command {
	int					pid;
	int					errnum;
	t_return			result;
	char				*cmd;
	struct s_envp		*argv;
	struct s_re			*re;
	struct s_fd			*fd;
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
	char				*pwd;
	struct sigaction	response;
	struct sigaction	child;
}				t_data;

typedef struct s_parse {
	int					i;
	int					start;
	int					i_string;
	struct s_envp		*str;
}				t_parse;

typedef struct s_parser {
	char				*tmp;
	char				*token;
	struct s_command	*cmd;
	int					len;
	int					inside_echo;
	int					result;
}				t_parser;

//ft_signals.c
void			ft_set_parent_interactive(void);
void			ft_set_parent_active(void);
void			ft_set_parent_heredoc(void);
void			ft_set_child_active(void);

//ft_signal_handler.c
void			ft_parent_interactive_sigint(int sign);
void			ft_parent_active_sigint(int sign);
void			ft_parent_active_sigquit(int sign);
void			ft_bash_sigint(int sign);

//ft_minishell.c
int				ft_cycle_cmd(t_data *data);
void			ft_initialize(t_data *data, char **envp);
void			ft_wait_for_kids(t_data *data);
void			ft_clear_mem(t_data *data);

//ft_error0.c
int				ft_print_error(t_command *cmd, int errnum, char *filename);
int				ft_error_codes(t_command *cmd);

//ft_error1.c
void			ft_err_file_cmd(t_command *cmd);
void			ft_err_syntax(t_command *cmd, char *token);
void			ft_err_not_valid(t_command *cmd, char *token);
void			ft_err_numeric(t_command *cmd, char *token);
void			ft_err_too_arg(t_command *cmd);

//ft_error2.c
void			ft_err_cd_folder(t_command *cmd, char *token);
void			ft_err_else(t_command *cmd, int errnum);
void			ft_err_fd(t_command *cmd, char *token);
void			ft_err_file(t_command *cmd);

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
char			*ft_remove_char(char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_free(void *ptr);

//ft_utils3.c
long			ft_string_to_int(const char *nptr);
void			ft_write_fd(int fd, char *s);
void			ft_print_bits(int input);
void			ft_write_fd_nl(int fd, char *s);

//ft_utils4.c
int				ft_last_pos_in_string(char *s, char c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);

//ft_utils5.c
size_t			ft_replace_in_string(char *s, char c_replace, char c_with);

//ft_parser0.c
void			ft_init_parser(t_parser *parser, t_data *data);
int				ft_check_heredoc_end_term(char *s);
void			ft_parser(t_data *data);
int				ft_end_of_token(char *s, int *inside_echo);
int				ft_find_end_of_token(char *s, int *inside_echo);

//ft_parser1.c
void			ft_inside_d_quote(t_parse *check, char *input, t_data *data);
void			ft_inside_s_quote(t_parse *check, char *input);
void			ft_found_dollar(t_parse *check, char *input, t_data *data);
char			*ft_prepare_output(t_envp *list);
char			*ft_get_next_token(t_parser *parser, t_data *data);

//ft_parser2.c
int				ft_check_cmd(t_data *data, t_parser *parser);
void			ft_check_quote(char c, int *d_quote, int *s_quote);
int				ft_len_whitespaces(const char *s);
char			*ft_skip_whitespaces(const char *str);
char			*ft_check_quotes_insert_var(t_parser *par, t_data *data);

//ft_parser3.c
t_return		ft_do_valid_redirections(t_data *data);
int				ft_check_next_token(t_command *cmd, char *file);
t_return		ft_redirect_(t_command *cmd, t_re *re,
					t_return (*redirect)(t_command *, t_re *));
void			ft_inside_echo(t_parser *parser);
int				ft_redirect_prepare_in_in(t_data *data,
					t_command *cmd, char *end_term);

//ft_parser4.c
char			*ft_found_hash(char *input);
void			ft_add_string(t_parse *check, char *input);
char			*ft_check_dollar_in_heredoc(char *token, t_data *data);
void			ft_questionmark(t_parse *check, t_data *data);
t_return		ft_check_for_asterisk(t_parser *parser, char *input);

//ft_parser5.c
void			ft_parser_add_argv(t_data *data, t_parser *parser);

//ft_exit.c
int				ft_exit(t_command *cmd, t_data *data);
int				ft_is_number_only(char *input);

//ft_env0.c
t_envp			*ft_copy_envp(char **envp);
t_envp			*ft_lstnew(char *content);
t_envp			*ft_lstlast(t_envp *lst);
void			ft_lstadd_back(t_envp **lst, t_envp *new);
void			ft_delete_list(t_envp **lst);

//ft_env1.c
int				ft_env(t_data *data, t_command *cmd);
char			*ft_get_var(char *s);
int				ft_str_var_cmp(char *var_name, char *var_elem);
t_envp			*ft_get_envp_element(t_envp *lst, char *var);
int				ft_count_of_envp(t_envp *envp);

//ft_env2.c
char			*ft_getenv(char *var, t_envp *envp_list);

//ft_commands0.c
t_command		*ft_create_cmd_elem(void);
void			ft_delete_cmd(t_command **commands);
t_command		*ft_create_cmd(char *cmd);
void			ft_print_commands(t_command *commands);
int				ft_build_in_exe(t_command *cmd, t_data *data);

//ft_commands1.c
int				ft_first_cmd(t_command *cmd, t_data *data);
t_command		*ft_last_cmd(t_command *cmd);

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
int				ft_pwd(t_data *data, t_command *cmd);

//ft_echo.c
int				ft_echo(t_command *cmd);
int				ft_valid_option(char *input);

//ft_cd.c
int				ft_cd(t_data *data, t_command *cmd);

//ft_pipe.c
int				ft_create_pipe(t_command *cmd);
int				ft_connect_pipe(t_command *cmd);
int				ft_close_pipe(t_command *cmd);
void			ft_close_child_fd(t_command *cmd, t_data *data);

//ft_executable.c
int				ft_do_execve(t_command *cmd, t_data *data);
char			*ft_check_path(char *cmd, char **paths);
char			**ft_create_envp_array(t_envp *envp);
void			ft_child_process(t_command *cmd, t_data *data, char *cmd_path);
char			**ft_create_argv_array(t_command *cmd);

//ft_split.c
char			**ft_split(char const *s, const char c);
size_t			ft_words_in_str(char const *s, const char c);
void			ft_free_char_array(char **array);

//ft_redirect0.c
t_return		ft_redirect_in(t_command *cmd, t_re *re);
t_return		ft_redirect_out(t_command *cmd, t_re *re);
t_return		ft_redirect_out_out(t_command *cmd, t_re *re);
t_return		ft_redirect_in_in(t_data *data, t_command *cmd, char *end_term);
int				ft_heredoc(t_data *data, int fd_out, char *end_term);

//ft_redirect1.c
t_re			*ft_lstnew_re(char *direct, char *file);
t_re			*ft_lstlast_re(t_re *lst);
void			ft_lstadd_back_re(t_re **lst, t_re *new);
void			ft_lstdel_re(t_re **re);
void			ft_get_re(t_data *data, t_parser *parser);

//ft_redirect2.c
void			ft_do_redirections(t_command *cmd, t_re *re);

//ft_get_next_line.c
char			*ft_get_next_line(int fd);

//ft_wildcard0.c
int				ft_wildcard(t_command *cmd, char *input);
t_envp			*ft_get_files(char *path);
char			**ft_get_filter(char *input);
t_envp			*ft_apply_filter(t_envp *full_list, char **filter);
t_return		ft_check_element(t_envp *full_list, char **filter,
					int len_first, int filter_size);

//ft_wildcard1.c
t_envp			*ft_prepare_list(char *input);
void			ft_get_filter_path(char *input, char **path, char **filter);

#endif
