/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 15:17:33 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			home = env[i] + 5;
			return (home);
		}
		i++;
	}
	return (NULL);
}

int	ft_cd(int argc, char **argv, char **env, t_cmd *cmd)
{
	char	*home;
	char	*new_home;

	if (argc == 2 && ft_strncmp(argv[1], "~", 1)
		&& ft_strncmp(argv[1], "-", 1) != 0)
	{
		if (chdir(argv[1]) != 0)
		{
			cmd->exit_code = 1;
			fail("failed to change directory");
		}
	}
	else if (argc == 1 || ft_strncmp(argv[1], "~", 1) == 0)
	{
		home = find_home(env);
		if (argv[1][0] == '~' && argv[1][1])
		{
			new_home = ft_strjoin(home, argv[1] + 1);
			home = new_home;
		}
		if (chdir(home) != 0)
			fail("failed to change directory with ~");
	}
	return (0);
}
