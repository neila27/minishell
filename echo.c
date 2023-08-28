/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/23 13:17:15 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(int argc, char **argv) 
{
	int i;

	i = 1;
	if (argc == 1) // argv0 echo
		printf("\n");
	else if (argc >= 2 && ft_strncmp(argv[1], "-n", 2) != 0) // argv0 echo argv1 -n
	{
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else if (argc >= 2) // argv0 echo argv1 neila 
	{
		i = 1;
		while (argv[i]) 
		{
			printf("%s", argv[i]);
			if (argv[i + 1])
				printf(" ");
			i++;
		}
	}
}