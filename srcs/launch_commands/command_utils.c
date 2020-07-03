/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:21:03 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 13:38:12 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commandlist(t_list *commandlist)
{
	t_list	*nav;
	t_list	*token_list;

	nav = commandlist;
	if (commandlist)
	{
		while (nav)
		{
			token_list = (t_list*)nav->content;
			ft_lstclear(&token_list, free);
			nav = nav->next;
		}
		free(commandlist);
	}
}

void	exit_minishell(int exit_code, int action, t_list **commandlist, char ***args)
{
	static t_list	**list_to_free;
	static char		***args_to_free;

	if (action == SAVE_POINTERS_TO_EXIT)
	{
		if (*commandlist)
			list_to_free = commandlist;
		if (*args)
			args_to_free = args;
		return ;
	}
	else if (action == EXIT_NOW)
	{
		if (list_to_free)
			free_commandlist(*list_to_free);
		if (args_to_free)
			free_argv(*args_to_free, INT_MAX);
	}
	exit (exit_code);
}
