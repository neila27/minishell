#include "minishell.h"

void	ft_env(char **env, int argc)
{
	int i;

	if (argc >= 1) // argv0 env 
	    fail("env no options");
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}