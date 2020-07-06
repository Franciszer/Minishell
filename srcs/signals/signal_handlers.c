/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 17:03:49 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void sigint_handler(int signo)
// {
// 	ft_printf("hello\n");
// 	//minishell_start();
// }

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\b\b\b\b\n");
		print_prompt();
	}
}

void signal_default()
{
	signal(SIGINT, SIG_DFL);
}