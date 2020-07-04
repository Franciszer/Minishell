/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:50:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 14:36:25 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*exit_filter(t_list **to_free, void *to_return, void (*del)(void *))
{
	ft_lstclear(to_free, del);
	return ((void*)to_return);
}

t_list		*ft_lstfilter_data(t_list **list, void *(*f)(void *, void*)\
			, void (*del)(void *), void *data)
{
	t_list	*new_list;
	void	*new_content;
	t_list	*nav;
	t_list	*nav_new;

	new_list = NULL;
	nav = *list;
	while (nav)
	{
		if (!(new_content = f(nav->content, data)))
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
