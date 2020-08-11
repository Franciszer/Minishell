/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 13:56:49 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/11 16:30:25 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*set_new_pwd(void)
{
	char	*pwd;
	char	**new_pwd;

	if (!(pwd = getcwd(NULL, 0)))
			return (NULL);
	if (!(new_pwd = malloc(sizeof(char*) * 3)))
		return (NULL);
	if (!(new_pwd[0] = ft_strdup("export")))
		return (NULL);
	if (!(new_pwd[1] = ft_strjoin("PWD=", pwd)))
		return (NULL);
	new_pwd[2] = NULL;
	builtin_export(new_pwd);
	free_argv(new_pwd, INT_MAX);
	return (pwd);
}

int				builtin_pwd(void)
{
	char	*pwd;

	if (!(pwd = get_env("PWD")) && !(pwd = set_new_pwd()))
	{
		return (1);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
