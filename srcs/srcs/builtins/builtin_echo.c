/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:44:06 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/18 11:43:13 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_trim(char **argv)
{
	char	**copy_trim;
	int		i;

	i = 0;
	while (argv[i])
		i++;
	if (!(copy_trim = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (!(copy_trim[i] = ft_strtrim(argv[i], " ")))
			return (NULL);
		i++;
	}
	copy_trim[i] = NULL;
	return (copy_trim);
}

int			builtin_echo(char **argv)
{
	int		i;
	char	option_n;
	char	**copy;

	i = 1;
	option_n = 0;
	while (!ft_strncmp(argv[i], "-n", 3))
	{
		option_n = 1;
		i++;
	}
	if (!(copy = copy_trim(argv)))
		return (1);
	if (copy[i])
		ft_putstr_fd(copy[i++], STDOUT_FILENO);
	while (copy[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(copy[i], STDOUT_FILENO);
		i++;
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	free_argv(copy, INT_MAX);
	return (0);
}
