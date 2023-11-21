/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 13:53:37 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace2(int *i, int *ir, char *new_str, char *env_changed)
{
	*ir += ft_strlen(env_changed);
	new_str = ft_strjoin_free(new_str, env_changed);
	*i += 1;
	return (new_str);
}

char	*replace3(int *ir, int *i, char *new_str, char *env_changed)
{
	(void)i;
	*ir += ft_strlen(env_changed);
	new_str = ft_strjoin_free(new_str, env_changed);
	return (new_str);
}

char	*setup_malloc(char *str)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		ft_error("Malloc error", 1);
	new_str[0] = '\0';
	return (new_str);
}

char	*get_env_value2(char *key, int exit_code)
{
	int		i;
	char	*result;
	char	*result_new;

	result = malloc(sizeof(char) * ft_strlen(key));
	i = 1;
	while (key[i])
	{
		result[i - 1] = key[i];
		i++;
	}
	result[i - 1] = '\0';
	result_new = ft_strjoin_free(ft_itoa(exit_code), result);
	return (result_new);
}
