/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/28 11:02:17 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void affiche_env(char **env) 
{
    int i;
    int j;
    int k;
    char *temp;
    
    i = 0;
    j = 0;
    while (i < size_table(env)) 
    {
        while (j < size_table(env) - i - 1) //-1 hors limite
        {
            if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0) 
            {
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    k = 0;
    while (k < size_table(env)) 
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

char **ft_export(int argc, char **argv, char **env) 
{
    int i;
    int j;
    size_t name_len;
    char *name;
    char *value;
    char *equal_pos;
    char **new_env;
    char *tmp_env;
    
    i = 0;
    value = NULL;
    name = NULL;
    if (argc == 2) 
    {
        equal_pos = ft_strchr(argv[2], '=');
        if (equal_pos)
        {
            value = equal_pos + 1;
            name = equal_pos - 1;
        }
    }
    name_len = ft_strlen(name);

    if (argc < 2 || argc >= 3)
        fail("Invalid number of args");
    else if (!ft_strisalpha(name))
        fail("only alpha plz");
    else if (ft_strncmp(argv[0], "export", 6) == 0)
        affiche_env(env);
    else if (argc == 2) 
    {
        while (env[i]) 
        {
            if (ft_strncmp(env[i], name, name_len) == 0 && (env[i])[name_len] == '=') 
            {
                j = 0;
                free(env[i]);
                tmp_env = ft_strjoin(name, "=");
                env[i] = ft_strjoin(tmp_env, value);
                free(tmp_env);
                return (env);
            }
            i++;
        }
    }
    j = 0;
    new_env = (char **)malloc((size_table(env) + 2) * sizeof(char *));
    while (env[j] != NULL) 
    {
        new_env[j] = env[j];
        j++;
    }
    new_env[size_table(env)] = ft_strdup(argv[2]);
    new_env[size_table(env) + 1] = NULL;
    return (new_env);
}
