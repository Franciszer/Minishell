/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:17:09 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 13:02:32 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_command_list(t_list *token_list)
{
	t_list	*command_list;
	t_list	*nav;
	t_list	*tmp;

	nav = token_list;
	tmp = NULL;
	if (!(command_list = ft_lstnew(token_list)))
		return (NULL);
	while (nav)
	{
		if (tmp && (nav->content && ((char*)nav->content)[0] == ';'))
		{
			tmp->next = NULL;
			tmp = nav;
			nav = nav->next;
			ft_lstdelone(tmp, free);
			if (!(tmp = ft_lstnew(nav)))
				return (NULL);
			ft_lstadd_back(&command_list, tmp);
		}
		else
		{
			tmp = nav;
			nav = nav->next;
		}
	}
	return (command_list);
}

int		execute_commands(t_list **commandlist, char **env)
{
	t_list	*nav;
	t_list	*token_list;
	char	**args;
	int		exit_status;

	nav = *commandlist;
	while (nav)
	{
		token_list = (t_list*)nav->content;
		token_list = expand_tokens(&token_list, env);
		if (!(args = list_to_argv(token_list)))
			return (0);
		exit_minishell(0, SAVE_POINTERS_TO_EXIT, commandlist, &args);
		exit_status = minishell_launch(args, env);
		free_argv(args, INT_MAX);
		nav = nav->next;
	}
	return (1);
}
