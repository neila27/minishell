#include "minishell.h"

void free_all_words(t_word *word)
{
	t_word *next_word;

	while (word != NULL)
	{
		free(word->text);
		next_word = word->next;
		free(word);
		word = next_word;
	}
}

void free_all_cmd(t_cmd **lst_cmd)
{
	int i;
	//int i2;

	i = 0;
	while (lst_cmd[i] != NULL)
	{
		/*i2 = 0;
		while (lst_cmd[i]->cmd[i2] != NULL)
		{
			//free(lst_cmd[i]->cmd[i2]);
			i2++;
		}*/
		free(lst_cmd[i]->cmd);
		free(lst_cmd[i]);
		i++;
	}
	free(lst_cmd);
}