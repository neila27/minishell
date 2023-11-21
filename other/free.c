/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:14:11 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_words(t_word *word)
{
	t_word	*next_word;

	while (word != NULL)
	{
		free(word->text);
		next_word = word->next;
		free(word);
		word = next_word;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_all_cmd(t_cmd **lst_cmd)
{
	int	i;
	int	u;

	u = 0;
	i = 0;
	while (lst_cmd[i] != NULL)
	{
		u = 0;
		while (lst_cmd[i]->cmd[u] != NULL)
		{
			free(lst_cmd[i]->cmd[u]);
			u++;
		}
		free(lst_cmd[i]->fd_input);
		free(lst_cmd[i]->fd_output);
		free(lst_cmd[i]->cmd);
		free(lst_cmd[i]);
		i++;
	}
	free(lst_cmd);
}

void	free_str_array(char **str_array)
{
	int	index;

	index = 0;
	while (str_array[index] != NULL)
	{
		free(str_array[index]);
		index++;
	}
	free(str_array);
}

t_word	*free_all_words_null(t_word *word)
{
	t_word	*next_word;

	while (word != NULL)
	{
		free(word->text);
		next_word = word->next;
		free(word);
		word = next_word;
	}
	return (NULL);
}
