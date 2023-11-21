/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/09/07 15:07:15 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint(void)
{
	struct sigaction	action;
	struct termios		termios_p;

	action.sa_handler = &handle_sigint;
	sigaction(SIGINT, &action, NULL);
	tcgetattr(0, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios_p);
}

void	sigquit(void)
{
	struct sigaction	action;
	struct termios		termios_p;

	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
	tcgetattr(0, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios_p);
}
/*ignorer 
get config du terminal 
c_lflag recoit input echoctl char ON par defaut &tilde
changer config du terminal*/

void	signals(void)
{
	sigint();
	sigquit();
}
