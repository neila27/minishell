/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/28 14:03:10 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    size_table(char **env)
{
    int count;

    count = 0;
    while (env[count])
        count ++;
    return (count);
}

char    **ft_unset(int argc, char **argv, char **env) 
{
    int i;
    char *name;
    char **new_env;
    
    new_env = malloc(sizeof(char *) * (size_table(env) - 1));
    if (new_env == NULL)
        return (NULL);
    name = argv[1];
    i = 0;
    if (argc == 1) // unset 
       printf("\n");
    else if (argc >= 3) // unset var trop
        fail("to many args");
    while (env[i])
    {
        if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=') 
        {
            while (env[i + 1])
            {
                free(env[i]);
                new_env[i] = env[i + 1];
                i++;
            }
            env[i] = NULL;
            break;
        } 
        i++;
    }
    free(env);
    return (new_env);
}

// env0 val1
// env1 val2
// env2 val3
// env3 val4

// ciao env1

// env0 val1
// env1 val3
// env2 val4
// env3 (valsuivante genre) val5