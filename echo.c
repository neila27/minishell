/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/16 15:13:50 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(int argc, char **argv) {
    int i;

    i = 2;
    if (argc == 2)
        printf("\n");
    else if (argc >= 3 && strncmp(argv[2], "-n", 2) != 0) {
        while (argv[i])
        {
            printf("%s", argv[i]);
            if (argv[i + 1])
                printf(" ");
            i++;
        }
        printf("\n");
    }
    else if (argc >= 3)
        i = 3;
        while (argv[i]) {
            printf("%s", argv[i]);
            if (argv[i + 1])
                printf(" ");
            i++;
        }
}

// int main(int argc, char **argv)
// {
// 	ft_echo(argc, argv);
// 	return 0;
// }