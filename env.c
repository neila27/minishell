#include "minishell.h"

// void fail(char *str)
// {
//     printf("%s\n", str);
//     exit(1);
// }

int	ft_env(char **env, int argc)
{
	int i;

	if (argc == 1)
	    fail("error env");
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	exit(1);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argv;
// 	ft_env(env, argc);
// 	return 0;
// }