/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:39:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 12:40:39 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*exit_filter(t_list **to_free, void *to_return, void (*del)(void *))
{
	ft_lstclear(to_free, del);
	return ((void*)to_return);
}

t_list		*ft_lstfilter(t_list **list, void *(*f)(void *)\
			, void (*del)(void *))
{
	t_list	*new_list;
	void	*new_content;
	t_list	*nav;
	t_list	*nav_new;

	new_list = NULL;
	nav = *list;
	while (nav)
	{
		if (!(new_content = f(nav->content)))
			nav = nav->next;
		else
		{
			if (!(nav_new = ft_lstnew(new_content)))
				return (exit_filter(&new_list, NULL, del));
			if (new_list)
				ft_lstadd_back(&new_list, nav_new);
			else
				new_list = nav_new;
			nav = nav->next;
		}
	}
	return (new_list);
}
