/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/05 17:56:30 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_launch(char **argv)
{
	pid_t	pid;
	char	*tmp;
	int		builtin_id;

	if ((builtin_id = is_builtin(argv[0])) >= 0)
		return ((g_exit_status = launch_builtin(builtin_id, argv)));
	else if (builtin_id == -2)
		return (-1);
	if (!(tmp = search_path(argv[0])))
	{
		ft_perror(ERR_UNKNOWN_COMMAND);
		return (1);
	}
	free(argv[0]);
	argv[0] = tmp;
	if (!(pid = fork()))
	{
		if (execve(argv[0], argv, g_env) == -1)
			ft_perror(ERR_EXECVE);
	}
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
	{
		waitpid(pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else
			g_exit_status = 1;
		
	}
	return (1);
}
