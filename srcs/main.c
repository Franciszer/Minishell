/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 11:12:43 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*token_list;
	t_list	*command_list;

	if (argc > 1 || argv[1])
	{
		ft_perror(ERR_TOO_MANY_ARGS);
		return (1);
	}
	g_env = env;
	while (1)
	{
		token_list = prompt_loop();
		if (!tokens_syntax_check(token_list))
		{
			ft_lstclear(&token_list, free);
			ft_perror(ERR_UNFINISHED_QUOTE);
		}
		else
		{
			if ((command_list = get_command_list(token_list)))
			{
				execute_commands(&command_list);
			}
			ft_lstclear(&token_list, free);
			free_commandlist(&command_list);
		}
	}
	return (0);	
}
