/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/21 12:00:42 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void fail(char *str)
// {
//     printf("%s\n", str);
//     exit(1);
// }

int ft_exit(int argc, char **argv)
{
	if (argc > 3)
		fail("too many args");
	else if (argc == 3)
	printf("normal exit");
    exit(0);
}

// int main(int argc, char **argv)
// {
// 	ft_exit(argc, argv);
// 	return 0;
// }