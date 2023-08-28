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
# include <fcntl.h>
# include <ctype.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>
# include "libft/libft.h"

enum token{
	GENERAL = -1,
	PIPE = '|',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	GREATER = '>',
	LESSER = '<',
	VAR = '$',
	DOUBLE_GREATER,
	DOUBLE_LESSER,
	IS_NULL = 0,
	OTHER
};

typedef struct s_word
{
	char			*text;
	enum	token	token;
	struct	s_word	*next;
	struct	s_word	*previous;
}	t_word;

typedef struct s_cmd
{
	char	**cmd;
	char	**envp;
	char	*fd_input;
	int		input_type;
	char	*fd_output;
	int		output_type;
}	t_cmd;

//?
t_cmd *check_redirection(t_cmd *cmd);


//lexer
t_word	*lexer(char *line);
t_word	*split_new_element(char *line, char c, int start);
int		token_error(t_word *current_word);
int		is_special_char(char word);
enum	token setup_token(char *word);

//quote
char		*remove_quote(char *text);
void		quote_close_check(t_word *current);
enum token	quote_status(enum token quote, char character);

//parser
t_cmd	*init_cmd(char **env, t_word *current);
t_cmd	**parser(t_word *start, char **env);

//pipe
void	change_stdout(t_cmd *cmd);
void	change_stdin(t_cmd *cmd);
void	redirect(t_cmd *cmd);
int		manage_pipe(t_cmd **lst_cmd);

//execute
int		execute_execve(char **cmd, char **envp);
int		execute_cmd(t_cmd *cmd);
char	*get_path(char *cmd, char **envp);
char	*get_base_name(char* path);

//env
char	*replace_env_vars(char *line);
int		replace_var_with_value(char *line, int line_index, char *result, int result_index);
char	*copy_substring(char *line, int start, int end);

//utils
void	create_file(char *file_name, int type);
// char	*ft_strjoin(char *s1, char *s2);
void	ft_error(char *msg);
int		number_of_pipe(t_word *word);
int		number_of_parameter(t_word *word);
int		number_of_parameter_cmd(char **cmd);

//free
void	free_all_words(t_word *word);
void	free_all_cmd(t_cmd **lst_cmd);
void	free_str_array(char **str_array);

//builtin
void	ft_echo(int argc, char **argv);
char 	**ft_unset(int argc, char **argv, char **env);
int		ft_pwd(void);
char	**ft_export(int argc, char **argv, char **env);
void	ft_cd(int argc, char **argv);
void	ft_env(char **env, int argc);
int		ft_exit(int argc);

//utilsneila
int		fail(char *str);
int		size_table(char **env);

//libft
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
// char	*ft_strdup(char*s1);
// int		ft_strlen(char *str);
// char	*ft_substr(char *s, unsigned int start, size_t len);


char	**ft_split(char *s, char c);
int		ft_split_len(char *s, char c);



//olc to delete
char* extract_between_triggers(const char* line, int start_index);
t_word	*split(char *line, char c);
char	*split_new_elem(char **cmd, char c);
char	**special_split(char *cmd, char c);

#endif