/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:18:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 14:23:45 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd(char **args)
{
	if (chdir(args[1]) < 0)
	{
		ft_perror(strerror(errno));
		return(1);
	}
	return(0);
}
