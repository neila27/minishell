/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 14:54:36 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	*cwd;

	(void)argc;
	(void)argv;
	cwd = malloc(PATH_MAX);
	if (cwd == NULL)
		return (0);
	if (getcwd(cwd, PATH_MAX) != 0)
		printf("%s\n", cwd);
	else
		fail("getcwd error\n");
	free(cwd);
	return (0);
}
