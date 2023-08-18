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

void	ft_export(int argc, char **argv, char *var, char **env)
{
	if (argc == 2)
		return (env_modifie(env, argc, var));
	else if (argc == 3)
		fail("too many args");
	if (ft_strisalpha(argv[3]) != 0)
		fail("only digit plz");
}
