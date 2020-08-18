/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:08:58 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/21 19:52:26 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*nav;

	if (!alst || !new)
		return ;
	nav = *alst;
	if (!nav)
		*alst = new;
	else
	{
		nav = ft_lstlast(nav);
		nav->next = new;
	}
}
