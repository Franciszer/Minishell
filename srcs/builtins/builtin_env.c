/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:06:01 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/21 13:33:41 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(void)
{
	int		i;

	i = 0;
	while (g_env[i])
		ft_putendl_fd(g_env[i++], STDOUT_FILENO);
	return (0);
}
