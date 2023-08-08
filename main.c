/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/07/18 16:31:37 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fail(char *str)
{
	ft_putstr_fd(str, 1);
	exit(1);
}

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
	struct termios        termios_p;
	
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
	//t_data		data;
	char		*str;

	(void) argc;
	(void) argv;
	(void) env;
	
	signals();
	add_history(str);
	while (1)
	{
		if ((str = readline("minishell$:")) == NULL)
			exit(1);
	}
	return (0);
}

