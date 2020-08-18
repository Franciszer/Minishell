/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/17 16:43:08 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_handler(int sig)
{
	g_open_pipe = 0;
	if (sig == SIGQUIT)
	{
		if (g_in_fork)
		{
			ft_printf("\n");
			g_exit_status = 131;
			print_prompt();
		}
		else
			ft_printf("\b\b  \b\b");
	}
}

void	sigint_handler(int sig)
{
	g_open_pipe = 0;
	if (sig == SIGINT)
	{
		if (!g_man)
		{
			g_exit_status = 1;
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
