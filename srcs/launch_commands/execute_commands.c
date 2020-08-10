/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:17:09 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 20:48:45 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (!(new_node_content = copy_command(nav))
				|| !(new_node = ft_lstnew(new_node_content)))
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

int		return_free_cmd(int type, char ***args, t_list **tmp_list)
{
	if (type == 2)
		free_argv(*args, INT_MAX);
	else
		ft_lstclear(tmp_list, free);
	return (0);
}


int		get_next_token(char *token, char *raw_token, t_list **tokenlist)
{
	t_list	*new;
	size_t	len;
	int		is_next;
	
	is_next = 0;
	len =  ftoken_len(raw_token);
	if (raw_token[len])
		len += ftoken_len(&raw_token[ftoken_len(raw_token)]);
	while (raw_token[len] && ft_isspace(raw_token[len]))
		len++;
	if (raw_token[len])
		is_next = 1;
	if (!(new = ft_lstnew(token)))
		return (0);
	if ((len == ft_strlen(raw_token)) || !is_next)
	{
		if ((*tokenlist)->next)
			new->next = (*tokenlist)->next;
	}
	else
	{
		if (!(new->next = ft_lstnew(ft_strdup(&raw_token[len]))))
			return (0);
		new->next->next = (*tokenlist)->next;				
	}
	ft_lstdelone(*tokenlist, free);
	*tokenlist = new;
	return (1);
}

int		identify_token(char *token_start, t_list **tokenlist)
{
	char	*token;
	char	*is_command;
	size_t	len;

	if((len = ftoken_len(token_start)) == ft_strlen(token_start))
		return (1);
	if (!(token = ft_strndup(token_start, ftoken_len(token_start))))
		return (0);
	is_command = NULL;
	if (is_builtin_child(token) != -1 || is_builtin_parent_2(token) ||\
	(is_command = search_path(token)))
	{
		if (is_command)
			free(is_command);
		if (!(get_next_token(token, token_start, tokenlist)))
			return (0);
		return (1);
	}
	else
		free(token);
	return (1);
}

int		execute_commands(t_list **commandlist)
{
	t_list	*nav;
	char	**args;
	t_list	*tmp_list;
	int		save;

	nav = *commandlist;
	save = 0;
	while (nav)
	{
		tmp_list = (t_list*)nav->content;
		if (!(nav->content = expand_tokens((t_list*)nav->content)))
			return (return_free_cmd(1, NULL, &tmp_list));
		if (!(identify_token(((t_list*)nav->content)->content, (t_list**)&(nav->content))))
		{
			printf("okbro\n");
			return return_free_cmd(1, NULL, &tmp_list);
		}
		ft_lstclear(&tmp_list, free);
		if (!(args = list_to_argv((t_list*)nav->content)))
			return (0);
		exit_minishell(SAVE_POINTERS_TO_EXIT, NULL, commandlist, &args);
		if (!(minishell_launch(args, &save, nav->next == NULL)))
			return (return_free_cmd(1, &args, NULL));
		free_argv(args, INT_MAX);
		nav = nav->next;
	}
	return (1);
}
