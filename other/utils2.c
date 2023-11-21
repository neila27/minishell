/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:16:46 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	number_of_pipe(t_word *word)
{
	int	count;

	count = 2;
	while (word != NULL)
	{
		if (word->token == PIPE)
			count++;
		word = word->next;
	}
	return (count);
}

int	number_of_parameter(t_word *word)
{
	int	count;

	count = 2;
	while (word->token != PIPE)
	{
		count++;
		word = word->next;
		if (!word)
			break ;
	}
	return (count);
}

char	*get_path2(char **all_path, char *final_path)
{
	free_str_array(all_path);
	return (final_path);
}
