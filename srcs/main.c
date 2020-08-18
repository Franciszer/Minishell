/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/17 12:40:19 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_and_throw(char *err, t_list **to_clear)
{
	ft_lstclear(to_clear, free);
	ft_perror(err);
}

void	minishell_start(void)
{
	t_list	*token_list;
	t_list	*command_list;

	if ((token_list = prompt_loop(0)))
	{
		if (!tokens_syntax_check(token_list))
			clear_and_throw(ERR_UNFINISHED_QUOTE, &token_list);
		else
		{
			command_list = get_command_list(token_list);
			execute_pipes(&command_list);
			ft_lstclear(&token_list, free);
			free_commandlist(&command_list);
		}
	}
	else
		return ;
}

int		main(int argc, char **argv, char **env)
{
	g_open_pipe = 0;
	g_pipe_error = 0;
	g_exit_status = 0;
	g_semicol_error = 0;
	g_man = 0;
	g_in_fork = 0;
	if (argc > 1 || argv[1])
	{
		ft_perror("ERR_TOO_MANY_ARGS");
		return (1);
	}
	g_env = env;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		if (!g_p_stop_sig)
			print_prompt();
		minishell_start();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_handler);
	}
	return (0);
}
