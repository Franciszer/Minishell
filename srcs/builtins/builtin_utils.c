/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:30:59 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/15 11:06:48 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_export_args(char **args)
{
	char	**new_args;
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
		i++;
	if (!(new_args = (char**)malloc(sizeof(char*) * ++i)))
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][ft_strlen(args[i]) - 1] == '=' && args[i + 1])
		{
			if (!(new_args[j] = ft_strjoin(args[i], args[i + 1])))
				return (NULL);
			i += 2;
			j++;	
		}
		else
		{
			if (!(new_args[j] = ft_strdup(args[i])))
				return (NULL);
			i++;
			j++;
		}		
	}
	new_args[j] = NULL;
	return (new_args);
}
