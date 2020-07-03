/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:18:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 14:26:29 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd(char **args, char **env)
{
	env = NULL;
	if (chdir(args[1]) < 0)
	{
		ft_perror(strerror(errno));
		return(1);
	}
	return(0);
}
