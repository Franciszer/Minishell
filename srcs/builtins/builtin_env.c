/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:06:01 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 14:08:39 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		ft_putendl_fd(env[i++], STDOUT_FILENO);
	return (0);
}
