/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:38:58 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 14:39:39 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_argv(char **argv, int max_index)
{
	int	i;

	if (argv)
	{
		i = 0;
		while (i < max_index && argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
	return (0);
}
