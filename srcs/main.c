/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:39:32 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 16:43:28 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_list	*token_list;
	char	**args;

	(void)argc;
	argv = NULL;
	while (1)
	{
		token_list = prompt_loop();
		if (minishell_exit(token_list))
		{
			ft_lstclear(&token_list, free);
			exit(0);
		}
		token_list = expand_tokens(&token_list, env);
		if (!(args = list_to_argv(token_list)))
			return (0);
		print_argv(args);
		ft_lstclear(&token_list, free);
		free_argv(args, INT_MAX);
	}
}
