/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_redirect(t_cmd *cmd, int fd[2])
{
	close(fd[0]);
	if (cmd->fd_input != NULL)
		change_stdin(cmd);
	if (cmd->fd_output != NULL)
		change_stdout(cmd);
	else
		dup2(fd[1], STDOUT_FILENO);
	execute_cmd(cmd);
	exit(0);
}

void	change_stdin(t_cmd *cmd)
{
	int	fd_temp;

	fd_temp = -1;
	if (cmd->input_type)
		fd_temp = open(cmd->fd_input, O_RDONLY);
	else
	{
		fd_temp = open("temp.txt", O_CREAT | O_RDWR, 0644);
		write(fd_temp, cmd->fd_input, ft_strlen(cmd->fd_input));
		close(fd_temp);
		fd_temp = open("temp.txt", O_RDONLY);
	}
	if (fd_temp == -1)
		ft_error("No such file or directory", 1);
	dup2(fd_temp, STDIN_FILENO);
	close(fd_temp);
}

void	change_stdout(t_cmd *cmd)
{
	int	fd_temp;

	if (cmd->output_type)
		fd_temp = open(cmd->fd_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_temp = open(cmd->fd_output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_temp == -1)
		ft_error("Can't open or create the file", 1);
	dup2(fd_temp, STDOUT_FILENO);
	close(fd_temp);
}

void	restore_original_fd(int original_stdin, int original_stdout)
{
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
}
