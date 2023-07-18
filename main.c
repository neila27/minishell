/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/07/18 15:32:46 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	nbr_args(t_token_list *token_list, t_data *data)
// {
// 	while (token_list)
// 	{
// 		if (token_list == WORD || token_list == STR)
// 			data->nbr_token ++;
// 		token_list = token_list->next;
// 	}
// 	return (data->nbr_token);
// }

// int	create_cmd(t_data *data, t_token_list *token_list)
// {
// 	char *args;
// 	int i;

// 	i = 0;
// 	data->nbr_token = nbr_args(&token_list);
// 	args = ft_calloc(sizeof(char *), (nbr_args + 1));
// 	if (args == NULL)
// 		ft_fail("error calloc for args")
// 	tmp = t_token_list[i];
// 	while (tmp)
// 	{
// 		if (data->tmp->type == PIPE || data->tmp->type == END)
// 			break ;
// 		if (put_args() != 0)
// 			ft_fail("failed to put args"));
// 		tmp = t_token_list->next;
// 	}
// 	return (0);
// }

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
	while (1)
	{
		if ((str = readline("minishell$:")) == NULL)
			exit(1);
		
	}
	return (0);
}

