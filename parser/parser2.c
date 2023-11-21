/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*init_cmd(char **env, t_word *current, int *last_exit_code, int *i)
{
	t_cmd	*lst_cmd;

	(void)i;
	*i = 0;
	lst_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (lst_cmd == NULL)
		ft_error("Malloc error", 1);
	lst_cmd->cmd = malloc(sizeof(char *) * (number_of_parameter(current) + 2));
	if (lst_cmd->cmd == NULL)
		ft_error("Malloc error", 1);
	lst_cmd->cmd[0] = NULL;
	lst_cmd->envp = env;
	lst_cmd->fd_input = NULL;
	lst_cmd->fd_output = NULL;
	lst_cmd->exit_code = *last_exit_code;
	return (lst_cmd);
}

t_word	*redirect_lesser(t_cmd *cmd, t_word *current)
{
	int		fd_temp;
	char	*copy;

	cmd->fd_input = current->next->text;
	if (current->token == LESSER)
	{
		copy = malloc(sizeof(char) * (ft_strlen(cmd->fd_input) + 1));
		ft_strlcpy(copy, cmd->fd_input, ft_strlen(cmd->fd_input) + 1);
		copy = remove_quote(copy);
		fd_temp = open(copy, O_RDONLY);
		free(copy);
		if (fd_temp == -1)
			return (NULL);
		close(fd_temp);
		cmd->input_type = 1;
	}
	else
		cmd->input_type = 0;
	if (current->next->next == NULL)
		return (NULL);
	else
		current = current->next;
	return (current);
}

t_word	*redirect_greater(t_cmd *cmd, t_word *current)
{
	current->next->text = remove_quote(current->next->text);
	cmd->fd_output = current->next->text;
	if (current->token == GREATER)
		cmd->output_type = 1;
	else
		cmd->output_type = 0;
	create_file(cmd->fd_output, cmd->output_type);
	if (current->next->next == NULL)
		return (NULL);
	else
		current = current->next;
	return (current);
}

enum e_token	is_quote(enum e_token is_open, enum e_token type)
{
	if (is_open == type)
		is_open = IS_NULL;
	else if (is_open == IS_NULL)
		is_open = type;
	return (is_open);
}
