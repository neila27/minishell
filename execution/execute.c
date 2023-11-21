/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**execute_cmd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		ft_echo(number_of_parameter_cmd(cmd->cmd) - 1, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		ft_env(cmd->envp, number_of_parameter_cmd(cmd->cmd) - 1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		ft_pwd(number_of_parameter_cmd(cmd->cmd) - 1, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "export", 7) == 0
		|| ft_strncmp(cmd->cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (cmd->envp);
	else
		execute_execve(cmd->cmd, cmd->envp);
	return (cmd->envp);
}

int	execute_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ft_exit(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		cmd->envp = ft_export(number_of_parameter_cmd(cmd->cmd) - 1,
				cmd->cmd, cmd->envp);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		ft_cd(number_of_parameter_cmd(cmd->cmd) - 1,
			cmd->cmd, cmd->envp, cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		cmd->envp = ft_unset(number_of_parameter_cmd(cmd->cmd) - 1,
				cmd->cmd, cmd->envp);
	else
		return (1);
	return (0);
}

int	execute_execve(char **cmd, char **envp)
{
	char	*path;

	path = get_path(cmd[0], envp, 0);
	cmd[0] = get_base_name(cmd[0]);
	if (!path)
	{
		free(path);
		return (ft_error("Command not found...", 127));
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		return (ft_error("Command execution fail...", 2));
	}
	free(path);
	return (0);
}

char	*get_path(char *cmd, char *envp[], int index)
{
	char	*final_path;
	char	*path_with_slash;
	char	**all_path;

	if (strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[index] != NULL && ft_strncmp(envp[index], "PATH", 4) != 0)
		index++;
	if (envp[index] == NULL)
		ft_error("command not found...", 127);
	all_path = ft_split(envp[index] + 5, ':');
	index = 0;
	while (all_path[index] != 0)
	{
		path_with_slash = ft_strjoin(all_path[index], "/");
		final_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(final_path, F_OK) == 0)
			return (get_path2(all_path, final_path));
		free(final_path);
		index++;
	}
	free_str_array(all_path);
	return (0);
}

char	*get_base_name(char *path)
{
	char	*base_name;

	base_name = strrchr(path, '/');
	if (base_name)
		return (base_name + 1);
	return (path);
}
