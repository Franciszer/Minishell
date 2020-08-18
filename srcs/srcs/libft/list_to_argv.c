/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:36:34 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/21 19:46:10 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**list_to_argv(t_list *token_list)
{
	int		len;
	char	**argv;
	int		i;

	i = 0;
	len = ft_lstlen(token_list);
	if (!(argv = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	argv[len] = NULL;
	while (i < len)
	{
		if (!(argv[i] = ft_strdup((char*)token_list->content)))
		{
			free_argv(argv, i);
			return (NULL);
		}
		token_list = token_list->next;
		i++;
	}
	return (argv);
}
