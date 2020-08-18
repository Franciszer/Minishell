/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:16:23 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/10 13:12:17 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*copy_command_p(t_list *command_start)
{
	t_list	*command_copy;
	char	*token_copy;
	t_list	*nav;
	t_list	*node_copy;

	nav = command_start;
	token_copy = NULL;
	command_copy = NULL;
	while (nav && nav->content && ((char*)nav->content)[0] != '|')
	{
		if (!(token_copy = ft_strdup((char*)nav->content))
			|| !(node_copy = ft_lstnew(token_copy)))
			return (NULL);
		if (!command_copy)
			command_copy = node_copy;
		else
			ft_lstadd_back(&command_copy, node_copy);
		nav = nav->next;
	}
	return (command_copy);
}

t_list	*get_command_list_p(t_list *token_list)
{
	t_list	*command_list;
	t_list	*nav;
	t_list	*new_node;
	t_list	*new_node_content;

	nav = token_list;
	command_list = NULL;
	while (nav)
	{
		if (nav->content && ((char*)nav->content)[0] != '|')
		{
			if (!(new_node_content = copy_command_p(nav))
				|| !(new_node = ft_lstnew(new_node_content)))
				return (NULL);
			if (!command_list)
				command_list = new_node;
			else
				ft_lstadd_back(&command_list, new_node);
			while (nav && nav->content && ((char*)nav->content)[0] != '|')
				nav = nav->next;
		}
		if (nav)
			nav = nav->next;
	}
	return (command_list);
}

int		execute_pipes(t_list **commandlist)
{
	t_list *unpiped_commandlist;
	t_list *nav;
	t_list *tmp_list;

	nav = *commandlist;
	while (nav)
	{
		tmp_list = (t_list*)nav->content;
		unpiped_commandlist = get_command_list_p(tmp_list);
		execute_commands(&unpiped_commandlist);
		free_commandlist(&unpiped_commandlist);
		nav = nav->next;
	}
	return (1);
}
