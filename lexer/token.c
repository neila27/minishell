/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/09/08 14:23:11 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum e_token	setup_token(char *word)
{
	if (word[0] == '\'')
		return (QUOTE);
	if (word[0] == '\"')
		return (DOUBLE_QUOTE);
	if (word[0] == '>')
	{
		if (word[1] == '>' && word[2] == '\0')
			return (DOUBLE_GREATER);
		else if (word[1] == '\0')
			return (GREATER);
		else
			return (ERROR);
	}
	if (word[0] == '<')
		return (setup_token2(word));
	if (word[0] == '|')
	{
		if (word[1] == '|')
			return (ERROR);
		return (PIPE);
	}
	return (OTHER);
}

enum e_token	setup_token2(char *word)
{
	if (word[1] == '<' && word[2] == '\0')
		return (DOUBLE_LESSER);
	else if (word[1] == '\0')
		return (LESSER);
	else
		return (ERROR);
}

int	error_check_token(t_word *current, t_word *start_word)
{
	if (current->token == DOUBLE_GREATER || current->token == DOUBLE_LESSER
		|| current->token == GREATER || current->token == LESSER
		|| current->token == PIPE || start_word->token == PIPE)
	{
		ft_error_without_exit("syntax error near unexpected token", 258);
		free_all_words(start_word);
		return (1);
	}
	current->next = NULL;
	current = start_word;
	if (token_error(current))
	{
		ft_error_without_exit("syntax error near unexpected token", 258);
		free_all_words(start_word);
		return (1);
	}
	return (0);
}

void	*error_from_token_setup(t_word *current_word, t_word *start_word)
{
	ft_error_without_exit("syntax error near unexpected token", 258);
	current_word->next = NULL;
	free_all_words(start_word);
	return (NULL);
}

int	token_error(t_word *current)
{
	int		repeat;
	t_word	*past_word;

	repeat = 0;
	past_word = current;
	while (current != NULL)
	{
		if ((current->token == GREATER || current->token == LESSER
				|| current->token == PIPE || current->token == DOUBLE_GREATER
				|| current->token == DOUBLE_LESSER)
			&& !(current->token == PIPE && (current->token == GREATER
					|| current->token == DOUBLE_GREATER)))
			repeat++;
		else if (!(past_word->token == PIPE && (current->token == GREATER
					|| current->token == DOUBLE_GREATER
					|| current->token == LESSER)))
			repeat = 0;
		if (repeat == 2)
			return (1);
		past_word = current;
		current = current->next;
	}
	return (0);
}
