/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 13:53:37 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 1)
		printf("\n");
	if (argc >= 2 && ft_strncmp(argv[1], "-n", 3) != 0)
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[++i])
				printf(" ");
		}
		printf("\n");
	}
	else if (argc >= 2)
	{
		i = 2;
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[++i])
				printf(" ");
		}
	}
}
