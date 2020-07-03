/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:27:08 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 15:34:43 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_argv_to_list(char **argv)
{
	int		i;
	t_list	*list;
	t_list	*new;
	char	*tmp;

	if (!argv)
		return (NULL);
	i = 0;
	list = NULL;
	while (argv[i])
	{
		if (!(tmp = ft_strdup(argv[i])))
			return (NULL);
		if (!(new = ft_lstnew((void*)tmp)))
			return (NULL);
		if (!list)
			list = new;
		else
			ft_lstadd_back(&list, new);
		i++;
	}
	return (list);
}
