/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:06:01 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 10:46:12 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env()
{
	int		i;

	i = 0;
	while (g_env[i])
		ft_putendl_fd(g_env[i++], STDOUT_FILENO);
	return (0);
}
