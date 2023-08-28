#include "minishell.h"

t_cmd	**parser(t_word *start, char **env)
{
	t_cmd	**lst_cmd;
	t_word	*current;
	int		i;
	int		i_cmd;

	current = start;
	//init variable of my first command
	lst_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * number_of_pipe(current));
	lst_cmd[0] = init_cmd(env, current);

	//verify if quote are close or print error
	quote_close_check(current);
	current = start;

	i = 0;
	i_cmd = 0;
	while (current != NULL)
	{
		//if token is pipe start new command
		if (current->token == PIPE)
		{
			lst_cmd[i_cmd]->cmd[i] = NULL;
			i_cmd++;
			lst_cmd[i_cmd] = init_cmd(env, current);
			i = 0;
		}
		//if token is quote remove it
		else if (current->token == QUOTE || current->token == DOUBLE_QUOTE)
		{
			current->text = remove_quote(current->text);
			lst_cmd[i_cmd]->cmd[i] = current->text;
			i++;
		}
		//if token is >> or > setup for change the stdout later
		else if (current->token == GREATER || current->token == DOUBLE_GREATER)
		{
			lst_cmd[i_cmd]->fd_output = current->next->text;
			if (current->token == GREATER)
				lst_cmd[i_cmd]->output_type = 1;
			else 
				lst_cmd[i_cmd]->output_type = 0;

			create_file(lst_cmd[i_cmd]->fd_output, lst_cmd[i_cmd]->output_type);

			if (current->next->next == NULL)
				break ;
		}
		//if token is << or < setup for change the stdin later
		else if (current->token == LESSER || current->token == DOUBLE_LESSER)
		{
			lst_cmd[i_cmd]->fd_input = current->next->text;

			if (current->token == LESSER)
				lst_cmd[i_cmd]->input_type = 1;
			else 
				lst_cmd[i_cmd]->input_type = 0;

			if (current->next->next == NULL)
				break ;
		}
		//default if just simple text
		else
		{
			lst_cmd[i_cmd]->cmd[i] = current->text;
			i++;
		}
		current = current->next;
	}
	lst_cmd[i_cmd]->cmd[i] = NULL;
	lst_cmd[i_cmd + 1] = NULL;
	return (lst_cmd);
}

void create_file(char *file_name, int type)
{
	int	fd_temp;

	if (type)
		fd_temp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_temp = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd_temp);
}

//verify if every quote is close at the end of the list of words
void	quote_close_check(t_word *current)
{
	int			i;
	enum token	is_open;

	is_open = IS_NULL;
	while (current != NULL)
	{
		i = 0;
		while (current->text[i])
		{
			if (current->text[i] == QUOTE)
			{
				if (is_open == QUOTE)
					is_open = IS_NULL;
				else if (is_open == IS_NULL)
					is_open = QUOTE;
			}
			else if (current->text[i] == DOUBLE_QUOTE)
			{
				if (is_open == DOUBLE_QUOTE)
					is_open = IS_NULL;
				else if (is_open == IS_NULL)
					is_open = DOUBLE_QUOTE;
			}
			i++;
		}
		current = current->next;
	}
	if (is_open != IS_NULL)
		ft_error("quote is open");
}

//initialize a new command
t_cmd	*init_cmd(char **env, t_word *current)
{
	t_cmd	*lst_cmd;

	(void)current;
	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lst_cmd->cmd = (char **)malloc(sizeof(char *) * number_of_parameter(current));

	lst_cmd->envp = env;
	lst_cmd->fd_input = NULL;
	lst_cmd->fd_output = NULL;
	return (lst_cmd);
}