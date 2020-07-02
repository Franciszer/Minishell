/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/02 18:29:32 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *command)
{
	if (!ft_strncmp(command, "cd", 3))
		return (0);
	else
		return (-1);
}

int		builtin_cd(char **args, char **env)
{
	env = NULL;
	if (chdir(args[1]) < 0)
	{
		ft_perror(strerror(errno));
		return (-1);
	}
	return (0);
}

int		launch_builtin(int builtin_id, char **argv, char **env)
{
	if (builtin_id == 0)
		return (builtin_cd(argv, env));
	else
		return (-1);
}

int		minishell_launch(char **argv, char **env)
{
	pid_t	pid;
	char	*tmp;

	if (is_builtin(argv[0]) >= 0)
		return (launch_builtin(is_builtin(argv[0]), argv, env));
	tmp = search_path(argv[0], env);
	free(argv[0]);
	argv[0] = tmp;
	if (!(pid = fork()))
	{
		if (execve(argv[0], argv, env) == -1)
			ft_perror(ERR_EXECVE);
	}
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
	{
		wait(&pid);
	}
	return (1);
}
