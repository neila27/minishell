#include "minishell.h"

// void fail(char *str)
// {
//     printf("%s\n", str);
//     exit(1);
// }

int ft_exit(int argc, char **argv)
{
	if (argc > 3)
		fail("too many args");
	else if (argc == 3)
	printf("normal exit");
    exit(0);
}

// int main(int argc, char **argv)
// {
// 	ft_exit(argc, argv);
// 	return 0;
// }