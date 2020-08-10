/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/09 13:01:01 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_handler(int sig)
{
	g_open_pipe = 0;
	if (sig == SIGQUIT)
	{
		ft_printf("\nQuit (core dumped)\n");
		g_exit_status = 131;
		print_prompt();
	}
}

void	sigint_handler(int sig)
{
	g_open_pipe = 0;
	if (sig == SIGINT)
	{
		if (!g_man)
		{
			ft_printf("\n");
			print_prompt();
		}
	}
}

void	signal_default(void)
{
	g_open_pipe = 0;
	signal(SIGINT, SIG_DFL);
}
