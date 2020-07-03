/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:30:42 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 13:40:28 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_exit(char **args)
{
	int		i;
	int		exit_code;

	i = 0;
	while (args[i])
		i++;
	exit_code = 0;
	if (i > 1 && !ft_is_strdigit(args[1]))
		exit_code = 255;
	else if (i > 2)
	{
		ft_perror(ERR_TOO_MANY_ARGS);
		return (1);
	}		
	exit_minishell(exit_code, EXIT_NOW, NULL, NULL);
	return (0);
}

