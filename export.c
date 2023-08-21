/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/21 12:02:49 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_modifie(char **env, int argc, char *var)
{
	int i;

	i = 0;
	while (env[i])
	{
		if(strchr(var, '=')) 
		{
			printf("%s\n", env[i]);
			i++;
		}
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

int	ft_export(int argc, char **argv, char *var, char **env, char *name, char *value) 
{
	char *var;
    size_t name_len;
    size_t value_len;
    size_t total_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	total_len = name_len + value_len + 2;
	if (argc == 2)
		env_modifie(env, argc, var);
	else if (argc == 4) 
		fail("too many args");
	else if (ft_strisalpha(argv[3]) != 0)
		fail("only digit plz");
	else if (argc == 3)
	{
    	*var = malloc(total_len);
    	if (var == NULL) 
			return (NULL);
    	ft_strcpy(var, name);
   		var[name_len] = '=';
    	ft_strcpy(var + name_len + 1, value); 
    	var[total_len - 1] = '\0';
    	putenv(var);
	}
	exit (1);
}

// int main(int argc, char **argv, char **env) 
// {
// 	char *name = argv[1];
// 	char *value = argv[2];
// 	char *digits = argv[3];

//     ft_export(argc, argv, env, name, value); ?????
//     printf("%s%s%s\n", name, value, digits);

//     return 0;
// }