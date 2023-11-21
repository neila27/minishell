/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_word	*lexer(char *line, int i, t_word *start_word, t_word *current_word)
{
	t_word	*previous_word;

	previous_word = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]) || line[i] == '\n')
			i++;
		if (line[i] == '\0')
			break ;
		current_word = split_new_element(line, ' ', i, IS_NULL);
		if (current_word->token == ERROR || current_word->token == '%')
			return (error_from_token_setup(current_word, start_word));
		i += ft_strlen(current_word->text);
		if (current_word->token == DOUBLE_LESSER)
			if (double_lesser(&current_word, &previous_word, &i, line))
				return (free_all_words_null(start_word));
		if (start_word != NULL)
			previous_word->next = current_word;
		else
			start_word = current_word;
		previous_word = current_word;
	}
	if (error_check_token(current_word, start_word))
		return (NULL);
	return (start_word);
}

t_word	*split_new_element(char *l, char c, int s, enum	e_token q)
{
	t_word	*r;
	int		e;

	r = (t_word *)malloc(sizeof(t_word));
	if (r == NULL)
		ft_error("Malloc error", 1);
	r->next = NULL;
	e = s;
	if (special_c(l[s]))
	{
		q = quote_status(q, l[e++]);
		while (q != IS_NULL && l[e])
			q = quote_status(q, l[e++]);
		while (l[s] == '$' && l[e] != ' ' && l[e] && special_c(l[e]) != 1)
			e++;
		if ((l[s] == '>' && l[s + 1] == '>')
			|| (l[s] == '<' && l[s + 1] == '<'))
			e++;
	}
	else
		while (l[e] != c && l[e] && special_c(l[e]) != 1)
			e++;
	r->text = ft_substr(l, s, e - s);
	r->token = special_token(l, s, e, r);
	return (r);
}

enum e_token	special_token(char *l, int s, int e, t_word *r)
{
	if (s != 0 && (l[s - 1] != ' ' && l[s - 1] != '|'
			&& l[s - 1] != '<' && l[s - 1] != '>'))
		r->token = CLOSE;
	else if (l[e] && l[e] != ' '
		&& (l[e - 1] == '\'' || l[e - 1] == '\"'))
		r->token = CLOSE_R;
	else
		r->token = setup_token(r->text);
	return (r->token);
}

int	double_lesser(t_word **current, t_word **previous, int *i, char *line)
{
	if (*previous == NULL)
	{
		ft_error_without_exit("syntax error near unexpected token", 1);
		return (1);
	}
	(*previous)->next = *current;
	*previous = *current;
	*current = get_word_redirection(line, i);
	if (*current == NULL)
	{
		return (1);
	}
	return (0);
}

int	special_c(char character)
{
	int	result;

	result = 0;
	if (character == '>' || character == '<' || character == '|'
		|| character == '\"' || character == '\'' || character == '$')
		result = 1;
	return (result);
}
