/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:44:06 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/18 11:18:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(char **argv)
{
	int		i;
	char	option_n;

	i = 1;
	option_n = 0;
	while (!ft_strncmp(argv[i], "-n", 3))
	{
		option_n = 1;
		i++;
	}
	if (argv[i])
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	while (argv[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	
	return (0);
}
