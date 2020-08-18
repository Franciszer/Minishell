/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:38:58 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 11:57:45 by qfeuilla         ###   ########.fr       */
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
