/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/08 14:07:34 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(char **argv)
{
	int	i;

	if (number_of_parameter_cmd(argv) > 3)
		fail_exit_other("too many args");
	else if (number_of_parameter_cmd(argv) == 2)
	{
		printf("exit\n");
		exit(0);
	}
	else if (number_of_parameter_cmd(argv) == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			if (ft_isalpha(argv[1][i]) == 1)
			{
				printf("exit\n");
				printf("bash: exit: numeric argument required\n");
				exit(255);
			}
			i++;
		}
		printf("exit\n");
		exit(ft_atoi(argv[1]));
	}
}
