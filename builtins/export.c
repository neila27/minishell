/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 14:47:29 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	trier_env(char **env)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	size = size_table(env);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	affiche_env(char **env)
{
	int	k;
	int	size;

	size = size_table(env);
	trier_env(env);
	k = 0;
	while (k < size)
	{
		printf("declare -x %s\n", env[k]);
		k++;
	}
}

static char	**update_new(char **env, char **split_res)
{
	int		j;
	char	**new_env;
	char	*tmp_env;

	j = 0;
	new_env = (char **)malloc((size_table(env) + 2) * sizeof(char *));
	if (new_env == NULL)
		ft_error("malloc error", 1);
	while (env[j] != NULL)
	{
		new_env[j] = env[j];
		j++;
	}
	tmp_env = ft_strjoin(split_res[0], "=");
	new_env[j] = ft_strjoin(tmp_env, split_res[1]);
	free(tmp_env);
	free_str_array(split_res);
	new_env[j + 1] = NULL;
	free(env);
	return (new_env);
}

static char	**parse_value(char **argv)
{
	char	**split_res;

	split_res = ft_split(argv[1], '=');
	if (split_res[1] && ft_strisgood(split_res[0]) == 1)
		return (split_res);
	else
		free_str_array(split_res);
	return (NULL);
}

char	**ft_export(int argc, char **argv, char **env)
{
	int		i;
	char	**split_res;

	i = 0;
	if (argc == 2)
		split_res = parse_value(argv);
	if (argc >= 3)
		fail("Invalid number of args");
	else if (argc == 1)
		affiche_env(env);
	else if (argc == 2 && split_res != NULL)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], split_res[0], ft_strlen(split_res[0])) == 0
				&& split_res[0][ft_strlen(split_res[0])] == '\0')
				return (update_existing_env(env, i, split_res));
			i++;
		}
		return (update_new(env, split_res));
	}
	return (env);
}
