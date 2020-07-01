/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:17:48 by frthierr          #+#    #+#             */
/*   Updated: 2020/06/29 12:21:29 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		free_argv(char **argv, int max_index)
{
	int	i;

	i = 0;
	while (i < max_index && argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
	return (0);
}

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
