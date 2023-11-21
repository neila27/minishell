/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 16:28:28 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_table(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count ++;
	return (count);
}

char	**unsetting(char **env, char **new_env, int i)
{
	free(env[i]);
	while (env[i + 1])
	{
		new_env[i] = env[i + 1];
		i++;
	}
	new_env[i] = NULL;
	free(env);
	return (new_env);
}

char	**ft_unset(int argc, char **argv, char **env)
{
	int		i;
	char	**new_env;

	i = -1;
	if (argc == 1)
		return (env);
	new_env = malloc(sizeof(char *) * (size_table(env)));
	if (new_env == NULL)
		return (NULL);
	while (env[++i])
	{
		new_env[i] = env[i];
		if (ft_strncmp(env[i], argv[1], ft_strlen(argv[1])) == 0
			&& env[i][ft_strlen(argv[1])] == '=')
			return (unsetting(env, new_env, i));
	}
	free(new_env);
	return (env);
}
