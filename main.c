#include "minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0); //remplacer contenue string vide 
		rl_on_new_line(); //curseur nouvelle ligne 
		rl_redisplay(); // afficher nouvelle ligne de commande (vide) 
	}
}

void	sigint(void)
{
	struct sigaction	action;
	struct termios        termios_p;
	
	action.sa_handler = &handle_sigint; //new prompt new line
	sigaction(SIGINT, &action, NULL);
	tcgetattr(0, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios_p);
	
}

void	sigquit(void)
{
	struct sigaction	action;
	struct termios		termios_p;
	
	action.sa_handler = SIG_IGN; //ignorer 
	sigaction(SIGQUIT, &action, NULL);
	tcgetattr(0, &termios_p); // get config du terminal 
	termios_p.c_lflag &= ~ECHOCTL; // c_lflag recoit input echoctl char ON par defaut &tilde pour 
	tcsetattr(0, TCSANOW, &termios_p); // changer config du terminal
}

void	signals(void)
{
	sigint();
	sigquit();
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_word 		*lst_word;
	t_cmd 		**lst_cmd;
	t_word 		*copy_word;


	(void)lst_cmd;
	(void)lst_word;
	(void) argc;
	(void) argv;
	(void) env;
	
	signals();

	while (1)
	{
		if ((line = readline("[minishell]$ ")) == NULL)
			exit(1);
		else
		{
			//printf("line : '%s'\n", line);
			lst_word = lexer(line);
			copy_word = lst_word;
			lst_cmd = parser(lst_word, env);
			env = lst_cmd[0]->envp;
			if (lst_cmd != NULL)
				manage_pipe(lst_cmd);
			free_all_words(copy_word);
			free_all_cmd(lst_cmd);
		}
		add_history(line);
	}
	return (0);
}

//press enter with empty command is crashing
//pipe is crashing ??
//when error show can get a new prompt
//double error showing


//ctr d need clean leak
