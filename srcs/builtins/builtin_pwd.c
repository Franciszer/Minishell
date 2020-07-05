/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:56:49 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 10:43:48 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd()
{
	char	*pwd;

	if (!(pwd=get_env("PWD")))
		return (1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
