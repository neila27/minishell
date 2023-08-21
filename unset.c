/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/21 12:01:25 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **env;

int ft_unset(int argc, char **argv, char *name) 
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
    exit(1);
}
