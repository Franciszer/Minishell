/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:06:01 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/14 12:57:17 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_empty(char *envvar)
{
	char	*end_of_key;

	end_of_key = ft_strchr((const char*)envvar, '=');
	if (!end_of_key)
		return (1);
	return (0);
}

int		builtin_env(void)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		if (!is_empty(g_env[i]))
			ft_putendl_fd(g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
