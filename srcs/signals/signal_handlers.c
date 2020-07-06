/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 21:53:31 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void sigint_handler(int signo)
// {
// 	ft_printf("hello\n");
// 	//minishell_start();
// }

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf("\nQuit (core dumped)\n");
		g_exit_status = 131;
		print_prompt();
	}
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\b\b\b\b\n");
		print_prompt();
	}
}

void	signal_default()
{
	signal(SIGINT, SIG_DFL);
}