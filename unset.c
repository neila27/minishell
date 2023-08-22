/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/22 12:42:04 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void fail(char *str)
// {
//     printf("%s\n", str);
//     exit(1);
// }

void    ft_unset(int argc, char **argv, char *name, char **env) 
{
    int i;

    i = 0;
    if (argc == 2)
        fail("not enough args");
    else if (argc > 3)
        fail("to many args");
    while (env[i])
    {
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=') 
        {
            while (env[i])
            {
                ft_bzero(env[i], ft_strlen(env[i]));
                i++;
            }
            break;
        }
        i++;
    }
}

// int main(int argc, char **argv, char **env) 
// {
//     char *name;
//     int i;
//     name = "VAR";
//     i = 0;
//     ft_unset(argc, argv, name, env);
//     while (env[i]) 
//     {
//         if (env[i][0]) 
//             printf("%s\n", env[i]);
//         i++;
//     }
//     return 0;
// }
