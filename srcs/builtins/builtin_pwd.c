/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:56:49 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/03 14:05:13 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **env)
{
	char	*pwd;

	if (!(pwd=get_env("PWD", env)))
		return (1);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
