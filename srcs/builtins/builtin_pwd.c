/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:56:49 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/21 13:33:10 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_pwd(void)
{
	char	*pwd;

	if (!(pwd = get_env("PWD")))
		return (1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
