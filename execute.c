#include "minishell.h"

int	execute_cmd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0) 
		ft_echo(number_of_parameter_cmd(cmd->cmd), cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0) 
		ft_env(cmd->envp, number_of_parameter_cmd(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0) 
		ft_exit(number_of_parameter_cmd(cmd->cmd));
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0) 
		cmd->envp = ft_export(number_of_parameter_cmd(cmd->cmd), cmd->cmd, cmd->envp);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0) 
		ft_pwd();
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		ft_cd(number_of_parameter_cmd(cmd->cmd), cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		cmd->envp = ft_unset(number_of_parameter_cmd(cmd->cmd), cmd->cmd, cmd->envp);
	else
		execute_execve(cmd->cmd, cmd->envp);
	return (0);
}

int	execute_execve(char **cmd, char **envp)
{
	char	*path;

	
	path = get_path(cmd[0], envp);
	cmd[0] = get_base_name(cmd[0]);
	
	if (!path)
		ft_error("Command not found");
	if (execve(path, cmd, envp) == -1)
		ft_error("Command execution fail");
	return (0);
}

char	*get_path(char *cmd, char *envp[])
{
	char	*final_path;
	char	**all_path;
	int		index;

	index = 0;
	while (ft_strncmp(envp[index], "PATH", 4) != 0)
		index++;
	all_path = ft_split(envp[index] + 5, ':');
	index = 0;
	while (all_path[index] != 0)
	{
		final_path = ft_strjoin(all_path[index], "/" );
		final_path = ft_strjoin(final_path, cmd);
		if (access(final_path, F_OK) == 0)
		{
			free_str_array(all_path);
			return(final_path);
		}
		free(final_path);
		index++;
	}
	free_str_array(all_path);
	return(0);
}

char	*get_base_name(char* path)
{
	char	*base_name;

	base_name = strrchr(path, '/');
	if (base_name)
		return (base_name + 1);
	return (path);
}

int	number_of_parameter_cmd(char **cmd)
{
	int count;

	count = 0;
	while (cmd[count] != NULL)
		count++;
	return (count + 1);
}


int	ft_split_len(char *s, char c)
{
	int		i;
	int		index_array;

	index_array = 1;
	i = 0;
	while (s[i++])
	{
		if (s[i] == c && s[i - 1] == c)
			index_array += 0;
		else if (s[i] == c || (s[i] == '\0' && s[i - 1] != c))
			index_array++;
	}
	return (index_array);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		index_array;
	int		past_po;
	char	**array;

	array = (char **)malloc(sizeof(*array) * ft_split_len(s, c));
	if (!array)
		return (0);
	index_array = 0;
	past_po = 0;
	i = 0;
	if (s[i] == c)
		past_po++;
	while (s[i++])
	{
		if (s[i] == c && s[i - 1] == c)
			past_po++;
		else if (s[i] == c || (s[i] == '\0' && s[i - 1] != c))
		{
			array[index_array++] = ft_substr(s, past_po, i - past_po);
			past_po = i + 1;
		}
	}
	array[index_array] = 0;
	return (array);
}
