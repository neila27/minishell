/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:16:18 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		i2;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 100));
	if (!dest)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2] != '\0')
	{
		dest[i] = s2[i2];
		i++;
		i2++;
	}
	free(s1);
	free(s2);
	dest[i] = '\0';
	return (dest);
}

int	ft_error(char *msg, int exit_code)
{
	printf("bash : %s\n", msg);
	exit(exit_code);
}

int	ft_error_without_exit(char *msg, int exit_code)
{
	(void)exit_code;
	printf("bash : %s\n", msg);
	return (1);
}

enum e_token	quote_status(enum e_token quote, char character)
{
	if (quote == QUOTE && character == QUOTE)
		quote = IS_NULL;
	else if (quote == DOUBLE_QUOTE && character == DOUBLE_QUOTE)
		quote = IS_NULL;
	else if (quote == IS_NULL && character == QUOTE)
		quote = QUOTE;
	else if (quote == IS_NULL && character == DOUBLE_QUOTE)
		quote = DOUBLE_QUOTE;
	return (quote);
}
