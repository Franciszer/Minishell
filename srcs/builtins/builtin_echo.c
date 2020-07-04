/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:44:06 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 20:00:28 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(char **argv)
{
	int		i;
	char	option_n;
	char	*str;
	
	i = 1;
	option_n = 0;
	if (!ft_strncmp(argv[1], "-n", 3))
	{
		option_n = 1;
		i++;
	}
	if (!(str = ft_strdup(argv[i++])))
		return (1);
	while (argv[i])
	{
		if (!(str = ft_strjoin_free(str, " ")))
				return (1);
		if (!(str = ft_strjoin_free(str, argv[i++])))
			return (1);
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
