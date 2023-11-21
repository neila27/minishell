/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:17:37 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quote(char *text)
{
	int		len;
	char	*final;

	len = ft_strlen(text);
	if (len < 2)
		return (text);
	final = (char *)malloc(len + 2);
	if (!final)
		return (NULL);
	final = remove_quote2(text, final, '\0');
	free(text);
	return (final);
}

char	*remove_quote2(char *text, char *final, char last)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (text[i])
	{
		if (text[i] == '"' || text[i] == '\'')
		{
			if (last == '\0')
				last = text[i++];
			else if (last == text[i])
			{
				i++;
				last = '\0';
			}
			else
				final[j++] = text[i++];
		}
		else
			final[j++] = text[i++];
	}
	final[j] = '\0';
	return (final);
}

int	line_is_empty(char *line)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (line[0] == '\t')
		return (0);
	while (line[i])
	{
		if (line[i] == '\t')
			return (0);
		if (line[i] != ' ' && line[i] != '\t')
			result = 1;
		i++;
	}
	return (result);
}

char	**env_copy(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	number_of_parameter_cmd(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count] != NULL)
		count++;
	return (count + 1);
}
