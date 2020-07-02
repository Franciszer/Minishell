/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 17:45:02 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*token_list;
	t_list	*command_list;

	(void)argc;
	argv = NULL;
	while (1)
	{
		token_list = prompt_loop();
		if (!tokens_syntax_check(token_list))
			ft_perror(ERR_UNFINISHED_QUOTE);
		else
		{
			command_list = get_command_list(token_list);
			if (command_list)
			{
				if (!execute_commands(command_list, env))
					return (0);
			}
		}
	}
}
