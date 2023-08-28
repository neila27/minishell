#include "minishell.h"

int	manage_pipe(t_cmd **lst_cmd)
{
	int	i;
	pid_t	process_end;

	i = 0;
	while (lst_cmd[i + 1] != NULL)
		redirect(lst_cmd[i++]);

	process_end = fork();
	if (process_end < 0)
		ft_error("Fork not working"); 
	if (process_end)
		waitpid(process_end, NULL, 0);
	else
	{
		if (lst_cmd[i]->fd_input != NULL)
			change_stdin(lst_cmd[i]);
		if (lst_cmd[i]->fd_output != NULL)
			change_stdout(lst_cmd[i]);
		execute_cmd(lst_cmd[i]);
	}
	return (0);
}

void redirect(t_cmd *cmd)
{
	int		fd[2];
	pid_t	process_id;

	if (pipe(fd) == -1)
		ft_error("Pipe not working"); 
	process_id = fork();
	if (process_id < 0)
		ft_error("Fork not working"); 
	if (process_id)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(process_id, NULL, 0);
	}
	else
	{
		close(fd[0]);
		if (cmd->fd_input != NULL)
			change_stdin(cmd);
		if (cmd->fd_output != NULL)
			change_stdout(cmd);
		else
			dup2(fd[1], STDOUT_FILENO);
		execute_cmd(cmd);
	}
}

void	change_stdin(t_cmd *cmd)
{
	int	fd_temp;

	fd_temp = -1;
	if(cmd->input_type)
		fd_temp = open(cmd->fd_input, O_RDONLY);
	else
	{
		printf("TO DO\n");
	}

	if (fd_temp == -1)
		ft_error("bash: No such file or directory !");
	dup2(fd_temp, STDIN_FILENO);
	close(fd_temp);
}

void	change_stdout(t_cmd *cmd)
{
	int	fd_temp;

	if(cmd->output_type)
		fd_temp = open(cmd->fd_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_temp = open(cmd->fd_output, O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (fd_temp == -1)
		ft_error("Can't open or create the file");
	dup2(fd_temp, STDOUT_FILENO);
	close(fd_temp);
}
