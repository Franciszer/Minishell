/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:20:05 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 12:02:32 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	if (!ft_strncmp(command, "cd", 3))
		return (BUILTIN_CD);
	else if (!ft_strncmp(command, "exit", ft_strlen("exit") + 1))
		return (BUILTIN_EXIT);
	else if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1))
		return (BUILTIN_PWD);
	else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
		return (BUILTIN_ENV);
	else if (!ft_strncmp(command, "echo", ft_strlen("echo") + 1))
		return (BUILTIN_ECHO);
	else if (!ft_strncmp(command, "export", ft_strlen("export") + 1))
		return (BUILTIN_EXPORT);
	else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
		return (BUILTIN_UNSET);
	else
		return (-1);
}

int		launch_builtin(int builtin_id, char **argv)
{
	if (builtin_id == BUILTIN_CD)
		return (builtin_cd(argv));
	else if (builtin_id == BUILTIN_EXIT)
		return (builtin_exit(argv));
	else if (builtin_id == BUILTIN_PWD)
		return (builtin_pwd());
	else if (builtin_id == BUILTIN_ENV)
		return (builtin_env());
	else if (builtin_id == BUILTIN_ECHO)
		return (builtin_echo(argv));
	else if (builtin_id == BUILTIN_EXPORT)
		return (builtin_export(argv));
	else if (builtin_id == BUILTIN_UNSET)
		return (builtin_unset(argv));
	else
		return (-1);
}