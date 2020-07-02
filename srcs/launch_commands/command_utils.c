/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:21:03 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 16:42:18 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commandlist(t_list *commandlist)
{
	t_list	*token_list;

	if (commandlist)
	{
		token_list = (t_list*)(commandlist->content);
		while (token_list)
		{
			ft_lstclear(&token_list, free);
			token_list = token_list->next;
		}
		free(commandlist);
	}
}
