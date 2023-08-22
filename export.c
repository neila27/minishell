/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/22 12:40:27 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>

// void fail(char *str)
// {
//     printf("%s\n", str);
//     exit(1);
// }

void env_modifie(char **env, int argc, char *var) 
{
    int count;
	int i;
	int j;
	
	count = 0;
	i = 0;
    while (env[count])
        count++;
    while (i < count) 
	{
        j = 0;
        while (j < count) 
		{
            if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) != 0)
			{
                char *temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    int k = 0;
    while (k < count) 
	{
        printf("declare -x %s\n", env[k]);
        k++;
    }
}

int ft_strisalpha(char *s)
{
    unsigned int i = 0;

    while (s[i])
    {
        if (!ft_isalpha(s[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_export(int argc, char **argv, char *var, char **env, char *name, char *value) 
{
    size_t name_len;
    size_t value_len;
    size_t total_len;

    name_len = ft_strlen(name);
    value_len = ft_strlen(value);
    total_len = name_len + value_len + 2;
    if (argc == 2 && argv[1] == "export")
        env_modifie(env, argc, var);
    else if (argc == 4) 
        fail("too many args");
    else if (ft_strisalpha(argv[3]) != 0)
        fail("only digit plz");
    else if (argc == 3)
    {
        var = (char *)malloc(total_len);
        if (var == 0) 
            return (0);
        ft_memcpy(var, name, name_len);
        var[name_len] = '=';
        ft_memcpy(var + name_len + 1, value, value_len);
        var[total_len - 1] = '\0';
        putenv(var);
    }
    free(var);
    return (0);
}

// int main(int argc, char **argv, char **env) 
// {
//     char *name = "VAR";
//     char *value = "value";
//     int i;

//     i = 0;
//     printf("Avant\n");
//     while (env[i]) 
// 	{
//         printf("%s\n", env[i]);
//         i++;
//     }
//     ft_export(2, argv, NULL, env, name, value); 
//     // ft_export(3, argv, NULL, env, name, value); 
//     // ft_export(4, argv, NULL, env, name, value);
//     printf("Après\n");
//     i = 0;
//     while (env[i]) 
// 	{
//         printf("%s\n", env[i]);
//         i++;
//     }
//     return (0);
// }
