/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:17:09 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/15 13:55:41 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*copy_command(t_list *command_start)
{
	t_list	*command_copy;
	char	*token_copy;
	t_list	*nav;
	t_list	*node_copy;

	nav = command_start;
	token_copy = NULL;
	command_copy = NULL;
	while (nav && nav->content && ((char*)nav->content)[0] != ';')
	{
		if (!(token_copy = ft_strdup((char*)nav->content)))
			return (NULL);
  		if (!(node_copy = ft_lstnew(token_copy)))
		{
			free(token_copy);
			return (NULL);
		}
		if (!command_copy)
			command_copy = node_copy;
		else
			ft_lstadd_back(&command_copy, node_copy);
		nav = nav->next;
	}
	return (command_copy);
}

t_list	*get_command_list(t_list *token_list)
{
	t_list	*command_list;
	t_list	*nav;
	t_list	*new_node;
	t_list	*new_node_content;
	
	nav = token_list;
	command_list = NULL;
	while (nav)
	{
		if (nav->content && ((char*)nav->content)[0] != ';')
		{
			if (!(new_node_content = copy_command(nav)))
				return (NULL);
			if (!(new_node = ft_lstnew(new_node_content)))
				return (NULL);
			if (!command_list)
				command_list = new_node;
			else
				ft_lstadd_back(&command_list, new_node);
			while (nav && nav->content && ((char*)nav->content)[0] != ';')
				nav = nav->next;
		}
		if (nav)
			nav = nav->next;
	}
	return (command_list);
}

int		execute_commands(t_list **commandlist)
{
	t_list	*nav;
	char	**args;
	t_list	*tmp_list;

	nav = *commandlist;
	while (nav)
	{
		tmp_list = (t_list*)nav->content;
		if (!(nav->content = expand_tokens((t_list*)nav->content)))
		{
			ft_lstclear(&tmp_list, free);
			return (0);
		}
		ft_lstclear(&tmp_list, free);
		if (!(args = list_to_argv((t_list*)nav->content)))
			return (0);
		exit_minishell(SAVE_POINTERS_TO_EXIT, NULL, commandlist, &args);
		if (!(minishell_launch(args)))
		{
			free_argv(args, INT_MAX);
			return (0);
		}
		free_argv(args, INT_MAX);
		nav = nav->next;
	}
	return (1);
}
