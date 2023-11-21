/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:12:30 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_var_in_str_new2(int *i, int *ir, char *new_str, char *str)
{
	new_str[*ir] = str[*i];
	new_str[*ir + 1] = '\0';
	*ir = *ir + 1;
	*i = *i + 1;
}

void	change_env_in_cmd(t_cmd **lst_cmd, char **envp)
{
	int		i;
	int		u;
	char	*new_str;
	char	*without_quotes;

	i = 0;
	u = 0;
	while (lst_cmd[u])
	{
		i = 0;
		if (lst_cmd[u]->fd_output != NULL)
			new_str = change_fd_output(lst_cmd[u], envp);
		if (lst_cmd[u]->fd_input != NULL)
			new_str = change_fd_input(lst_cmd[u], envp);
		while (lst_cmd[u]->cmd[i] != NULL)
		{
			new_str = replace_var_in_str_new(lst_cmd[u]->cmd[i],
					envp, lst_cmd[u]->exit_code, 0);
			without_quotes = remove_quote(new_str);
			free(lst_cmd[u]->cmd[i]);
			lst_cmd[u]->cmd[i] = without_quotes;
			i++;
		}
		u++;
	}
}

char	*change_fd_output(t_cmd *cmd, char **envp)
{
	char	*without_quotes;
	char	*new_str;

	new_str = replace_var_in_str_new(cmd->fd_output,
			envp, cmd->exit_code, 0);
	without_quotes = remove_quote(new_str);
	cmd->fd_output = without_quotes;
	return (new_str);
}

char	*change_fd_input(t_cmd *cmd, char **envp)
{
	char	*without_quotes;
	char	*new_str;

	new_str = replace_var_in_str_new(cmd->fd_input,
			envp, cmd->exit_code, 0);
	without_quotes = remove_quote(new_str);
	cmd->fd_input = without_quotes;
	return (new_str);
}

int	length_var(char *str, int start)
{
	int	end;

	end = start + 1;
	while ((str[end] == '_' || str[end] == '?'
			|| isalnum(str[end])) && str[end])
		end++;
	return (end - start);
}
