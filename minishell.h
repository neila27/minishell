/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <ctype.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include "libft/libft.h"

enum e_token
{
	ERROR = '1',
	PIPE = '|',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	GREATER = '>',
	LESSER = '<',
	VAR = '$',
	DOUBLE_GREATER = '2',
	DOUBLE_LESSER = '3',
	IS_NULL = 0,
	CLOSE = 10,
	CLOSE_R = 11,
	OTHER = '0'
};

typedef struct s_word
{
	char			*text;
	enum e_token	token;
	struct s_word	*next;
}	t_word;

typedef struct s_cmd
{
	char	**cmd;
	char	**envp;
	char	*fd_input;
	int		input_type;
	char	*fd_output;
	int		output_type;
	int		exit_code;
}	t_cmd;

//main
enum e_token	setup_token2(char *word);
enum e_token	setup_token(char *word);
char			**command_process(char *line, t_word *lst_word,
					int *last_exit_status, char **update_env);
enum e_token	special_token(char *l, int s, int e, t_word *r);

//lexer
t_word			*lexer(char *line, int i, t_word *start_word,
					t_word *current_word);
t_word			*split_new_element(char *line, char c, int start,
					enum	e_token quote);
int				token_error(t_word *current_word);
int				special_c(char word);
t_word			*get_word_redirection(char *line, int *i);
char			*get_delimiter(char *line, int *index);
int				error_check_token(t_word *current_word, t_word *start_word);
void			*error_from_token_setup(t_word *current_word,
					t_word *start_word);
char			*get_input_text(char *line, int index, int *result_index,
					int i_result);
int				is_end_of_delimeter(char *line, int index, char *delimiter,
					int *result_index);
void			free_end_redirect(char *delimiter, char *result);
int				double_lesser(t_word **current_word, t_word **previous_word,
					int *i, char *line);

//quote
char			*remove_quote(char *text);
int				quote_close_check(t_word *current);
enum e_token	quote_status(enum e_token quote, char character);

//parser
t_cmd			*init_cmd(char **env, t_word *current,
					int *last_exit_code, int *i);
t_cmd			**parser(t_word *start, char **env, int *last_exit_code,
					int i_cmd);
t_word			*redirect_lesser(t_cmd *cmd, t_word *current);
t_word			*redirect_greater(t_cmd *cmd, t_word *current);
enum e_token	is_quote(enum e_token is_open, enum e_token type);
t_word			*parser2(t_word *current, t_cmd **lst_cmd, int i_cmd, int *i);
t_cmd			**parser3(t_cmd **lst_cmd, int i_cmd, int i);

//pipe
void			change_stdout(t_cmd *cmd);
void			change_stdin(t_cmd *cmd);
void			redirect(t_cmd *cmd);
int				manage_pipe(t_cmd **lst_cmd, int i,
					int original_stdin, int original_stdout);
void			restore_original_fd(int original_stdin, int original_stdout);
void			write_env_to_pipe(int fd_env[2], char **message);
void			read_env_to_pipe(int fd_env[2], t_cmd *cmd, int i);
void			child_process(t_cmd **lst_cmd, int i);
void			child_process_redirect(t_cmd *cmd, int fd[2]);

//execute
int				execute_execve(char **cmd, char **envp);
char			**execute_cmd(t_cmd *cmd);
char			*get_path(char *cmd, char **envp, int index);
char			*get_base_name(char	*path);
int				execute_builtins(t_cmd *cmd);

//env
void			change_env_in_cmd(t_cmd **lst_cmd, char **envp);
char			*get_env_value(char *key, char **envp, int exit_code);
char			*copy_substring(char *line, int start, int end);
char			*replace_var_in_str_new(char *str, char **envp,
					int exit_code, int i);
char			*replace_var(char *str, int start, char **envp, int exit_code);
int				length_var(char *str, int start);
char			*ft_strjoin_free(char *s1, char *s2);
void			replace_var_in_str_new2(int *i, int *ir, char *new_str,
					char *str);

//utils
void			create_file(char *file_name, int type);
int				ft_error(char *msg, int exit_code);
int				number_of_pipe(t_word *word);
int				number_of_parameter(t_word *word);
int				number_of_parameter_cmd(char **cmd);
char			**env_copy(char **env);

//free
void			free_all_words(t_word *word);
void			free_all_cmd(t_cmd **lst_cmd);
void			free_str_array(char **str_array);
void			free_env(char **env);
int				ft_isspace(int c);
t_word			*free_all_words_null(t_word *word);

//builtin
void			ft_echo(int argc, char **argv);
char			**ft_unset(int argc, char **argv, char **env);
int				ft_pwd(int argc, char **argv);
char			**ft_export(int argc, char **argv, char **env);
int				ft_cd(int argc, char **argv, char **env, t_cmd *cmd);
int				size_table(char **env);
void			ft_env(char **env, int argc);
void			ft_exit(char **argv);
char			**update_existing_env(char **env, int i, char **split_res);
int				ft_strisgood(char *str);

//signals
void			signals(void);
void			sigquit(void);
void			sigint(void);
void			handle_sigint(int signal);

//other
char			**ft_split(char *s, char c);
int				ft_split_len(char *s, char c);
int				line_is_empty(char *line);
int				ft_error_without_exit(char *msg, int exit_code);
int				fail(char *msg);
char			*replace_var_relatif(char *str, int start,
					char **envp, int exit_code);
char			*change_fd_input(t_cmd *cmd, char **envp);
char			*change_fd_output(t_cmd *cmd, char **envp);
char			*get_path2(char **all_path, char *final_path);
char			*replace2(int *i, int *ir, char *new_str, char *env_changed);
char			*replace3(int *ir, int *i, char *new_str, char *env_changed);
char			*setup_malloc(char *str);
char			*remove_quote2(char *text, char *final, char last);
char			*get_env_value2(char *key, int exit_code);
int				fail_exit_other(char *str);

#endif