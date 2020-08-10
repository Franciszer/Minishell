/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:30:42 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 13:47:31 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_exit(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		g_exit_status = 1;
		ft_perror(ERR_TOO_MANY_ARGS);
		return (1);
	}
	else if (args[1] && (!ft_is_strdigit(args[1]) || ft_strlen(args[1]) > 10))
		g_exit_status = 255;
	else if (args[1])
		g_exit_status = ft_atoi(args[1]);
	exit_minishell(EXIT_NOW, NULL, NULL, NULL);
	return (0);
}
