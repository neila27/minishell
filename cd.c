/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Probook <Probook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:10:31 by nmuminov          #+#    #+#             */
/*   Updated: 2023/08/23 13:16:59 by Probook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd(int argc, char **argv)
{   
    if (argc < 2) // argv0 cd argv1 dir
        fail("not enough arg");
	else if (argc == 2)
    {
        if (access(argv[1], F_OK) == -1)
            fail("dir does not exist");
        else if (chdir(argv[1]) == -1)
            fail("failed to change dir");
    }
	else if (argc > 2)
        fail("too many args");
}