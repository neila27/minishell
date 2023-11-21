/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	**parser(t_word *start, char **env, int *last_exit_code, int i_cmd)
{
	t_cmd	**lst_cmd;
	t_word	*current;
	int		i;

	current = start;
	if (quote_close_check(current))
		return (NULL);
	lst_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * number_of_pipe(current));
	if (!lst_cmd)
		ft_error("Malloc error", 1);
	lst_cmd[0] = init_cmd(env, current, last_exit_code, &i);
	while (current != NULL)
	{
		if (current->token == PIPE)
		{
			lst_cmd[i_cmd++]->cmd[i] = NULL;
			lst_cmd[i_cmd] = init_cmd(env, current, last_exit_code, &i);
		}
		else
			current = parser2(current, lst_cmd, i_cmd, &i);
		if (current == NULL)
			break ;
		current = current->next;
	}
	return (parser3(lst_cmd, i_cmd, i));
}

t_word	*parser2(t_word *c, t_cmd **lst_cmd, int i_cmd, int *i)
{
	if (c->token == GREATER || c->token == DOUBLE_GREATER)
		c = redirect_greater(lst_cmd[i_cmd], c);
	else if (c->token == LESSER || c->token == DOUBLE_LESSER)
		c = redirect_lesser(lst_cmd[i_cmd], c);
	else if (c->token == 10)
		lst_cmd[i_cmd]->cmd[*i - 1] = ft_strjoin_free(
				lst_cmd[i_cmd]->cmd[*i - 1], ft_strdup(c->text));
	else if (c->token == 11)
	{
		lst_cmd[i_cmd]->cmd[*i] = ft_strjoin(c->text, c->next->text);
		*i = *i + 1;
		c = c->next;
	}
	else if (c->token == QUOTE || c->token == DOUBLE_QUOTE)
	{
		lst_cmd[i_cmd]->cmd[*i] = ft_strdup(c->text);
		*i = *i + 1;
	}
	else
	{
		lst_cmd[i_cmd]->cmd[*i] = ft_strdup(c->text);
		*i = *i + 1;
	}
	return (c);
}

t_cmd	**parser3(t_cmd **lst_cmd, int i_cmd, int i)
{
	lst_cmd[i_cmd]->cmd[i] = NULL;
	lst_cmd[i_cmd + 1] = NULL;
	return (lst_cmd);
}

void	create_file(char *file_name, int type)
{
	int	fd_temp;

	if (type)
		fd_temp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_temp = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	close(fd_temp);
}

//verify if every quote is close at the end of the list of words
int	quote_close_check(t_word *current)
{
	int				i;
	enum e_token	is_open;

	is_open = IS_NULL;
	while (current != NULL)
	{
		i = 0;
		while (current->text[i])
		{
			if (current->text[i] == QUOTE)
				is_open = is_quote(is_open, QUOTE);
			else if (current->text[i] == DOUBLE_QUOTE)
				is_open = is_quote(is_open, DOUBLE_QUOTE);
			i++;
		}
		current = current->next;
	}
	if (is_open != IS_NULL)
		return (ft_error_without_exit("Error : A quote is open", 1));
	return (0);
}
