/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_lesser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_word	*get_word_redirection(char *line, int *i)
{
	char	*result_text;
	int		result_index;
	t_word	*result;

	result_index = 0;
	result = (t_word *)malloc(sizeof(t_word));
	if (result == NULL)
		ft_error("Malloc error", 1);
	result_text = get_input_text(line, *i, &result_index, 0);
	if (result_text == NULL)
	{
		free(result);
		return (NULL);
	}
	result->text = result_text;
	result->token = setup_token(result->text);
	result->next = NULL;
	*i = result_index;
	return (result);
}

char	*get_input_text(char *line, int index, int *result_index, int i_result)
{
	char	*delimiter;
	char	*result;

	result = malloc(sizeof(char) * ft_strlen(line));
	if (result == NULL)
		ft_error("Malloc error", 1);
	delimiter = get_delimiter(line, &index);
	while (line[index])
	{
		if (line[index] == '\n')
		{
			if (is_end_of_delimeter(line, index, delimiter, result_index))
			{
				result[i_result] = '\n';
				result[i_result + 1] = '\0';
				return (result);
			}
		}
		if (!(i_result == 0 && line[index] == '\n'))
			result[i_result++] = line[index];
		index++;
	}
	free_end_redirect(delimiter, result);
	return (NULL);
}

char	*get_delimiter(char *l, int *index)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * ft_strlen(l));
	if (result == NULL)
		ft_error("Malloc error", 1);
	while (ft_isspace(l[*index]))
		*index += 1;
	while (l[*index] != '\n' && l[*index] != ' ' && l[*index] != '\0')
	{
		result[i] = l[*index];
		i++;
		*index += 1;
	}
	result[i] = '\0';
	while (ft_isspace(l[*index]))
		*index += 1;
	*index -= 1;
	return (result);
}

int	is_end_of_delimeter(char *line, int index, char *delimiter, int *r_index)
{
	int	i2;

	i2 = 0;
	while (line[index + i2 + 1] && line[index + i2 + 1] == delimiter[i2])
		i2++;
	if (delimiter[i2] == '\0' && line[index + i2 + 1] != ' ')
	{
		*r_index = index + i2 + 1;
		free(delimiter);
		return (1);
	}
	return (0);
}

void	free_end_redirect(char *delimiter, char *result)
{
	ft_error_without_exit("No end delimiter found", 1);
	free(delimiter);
	free(result);
}
