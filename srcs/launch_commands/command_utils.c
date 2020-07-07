/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:21:03 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/07 10:45:17 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(t_list	*command)
{
	t_list	*token_list;

	token_list = command;
	ft_lstclear(&token_list, free);
}

void		free_commandlist(t_list **commandlist)
{
	t_list	*nav;
	t_list	*tmp;

	if (!commandlist)
		return ;
	nav = *commandlist;
	if (*commandlist)
	{
		while (nav)
		{
			tmp = nav->next;
			free_command((t_list*)nav->content);
			free(nav);
			nav = tmp;
		}
	}
}

void		exit_minishell(int action, t_list *token_list, t_list **commandlist, char ***args)
{
	static t_list	*to_free;
	static t_list	**list_to_free;
	static char		***args_to_free;

	if (action == SAVE_POINTERS_TO_EXIT)
	{
		to_free = token_list;
		if (*commandlist)
			list_to_free = commandlist;
		if (*args)
			args_to_free = args;
		return ;
	}
	else if (action == EXIT_NOW)
	{
		if (to_free)
			ft_lstclear(&to_free, free);
		if (list_to_free)
			free_commandlist(list_to_free);
		if (args_to_free)
			free_argv(*args_to_free, INT_MAX);
	}
	system("leaks minishell");
	exit (g_exit_status);
}
