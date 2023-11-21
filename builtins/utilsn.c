/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 14:13:50 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fail(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	fail_exit_other(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	ft_strisgood(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_' || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

char	**update_existing_env(char **env, int i, char **split_res)
{
	char	*tmp_env;

	(void)tmp_env;
	free(env[i]);
	tmp_env = ft_strjoin(split_res[0], "=");
	env[i] = ft_strjoin(tmp_env, split_res[1]);
	free(tmp_env);
	free_str_array(split_res);
	return (env);
}
