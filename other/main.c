/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalvarez nmuminov                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:10:31 by lalvarez          #+#    #+#             */
/*   Updated: 2023/08/01 13:16:59 by lalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		**update_env;
	int			l_e;

	(void)argc;
	(void)argv;
	update_env = env_copy(env);
	l_e = 0;
	while (1)
	{
		signals();
		line = readline("[minishell]$ ");
		if (line == NULL)
			exit(1);
		else
		{
			if (line_is_empty(line))
				update_env = command_process(line, NULL, &l_e, update_env);
		}
		add_history(line);
	}
	return (0);
}

char	**command_process(char *line, t_word *lst_word, int *l_e, char **u)
{
	t_word		*copy_word;
	t_cmd		**lst_cmd;

	lst_word = lexer(line, 0, NULL, NULL);
	if (lst_word != NULL)
	{
		copy_word = lst_word;
		lst_cmd = parser(lst_word, u, l_e, 0);
		if (lst_cmd != NULL && lst_cmd[0]->cmd[0] != NULL)
		{
			change_env_in_cmd(lst_cmd, lst_cmd[0]->envp);
			manage_pipe(lst_cmd, 0, 0, 0);
			unlink("temp.txt");
			u = lst_cmd[0]->envp;
			*l_e = lst_cmd[0]->exit_code;
			free_all_cmd(lst_cmd);
		}
		else
			*l_e = 1;
		free_all_words(copy_word);
	}
	else
		*l_e = 2;
	return (u);
}
