/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_open_command = 0;

int	manage_pipe(t_cmd **lst_cmd, int i, int original_stdin, int original_stdout)
{
	int		exit_code;
	pid_t	process_end;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	while (lst_cmd[i + 1] != NULL && lst_cmd[i + 1]->cmd[0] != NULL)
		redirect(lst_cmd[i++]);
	process_end = fork();
	if (process_end < 0)
		ft_error("Fork not working", 1);
	if (process_end)
	{
		if (i == 0)
			execute_builtins(lst_cmd[i]);
		g_open_command = 1;
		waitpid(process_end, &exit_code, 0);
		g_open_command = 0;
		lst_cmd[0]->exit_code = WEXITSTATUS(exit_code);
	}
	else
		child_process(lst_cmd, i);
	restore_original_fd(original_stdin, original_stdout);
	return (0);
}

void	child_process(t_cmd **lst_cmd, int i)
{
	if (lst_cmd[i]->fd_input != NULL)
		change_stdin(lst_cmd[i]);
	if (lst_cmd[i]->fd_output != NULL)
		change_stdout(lst_cmd[i]);
	if (lst_cmd[i]->cmd[0] != NULL)
		execute_cmd(lst_cmd[i]);
	exit(0);
}

void	redirect(t_cmd *cmd)
{
	int		fd[2];
	pid_t	process_id;

	unlink("temp.txt");
	if (pipe(fd) == -1)
		ft_error("Pipe not working", 1);
	process_id = fork();
	if (process_id < 0)
		ft_error("Fork not working", 1);
	if (process_id)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(process_id, NULL, 0);
	}
	else
		child_process_redirect(cmd, fd);
}

void	write_env_to_pipe(int fd_env[2], char **message)
{
	char	delimiter;
	int		i;

	i = 0;
	delimiter = '\n';
	close (fd_env[0]);
	while (message[i] != NULL)
	{
		write(fd_env[1], message[i], ft_strlen(message[i]) + 1);
		write(fd_env[1], &delimiter, 1);
		free(message[i]);
		i++;
	}
	free(message);
	close(fd_env[1]);
}

void	handle_sigint(int signal)
{
	if (g_open_command == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
