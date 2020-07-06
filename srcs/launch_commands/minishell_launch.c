/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/06 18:13:37 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	sigtest(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}
int		minishell_launch(char **argv)
{
	pid_t	pid;
	char	*tmp;
	int		builtin_id;

	if ((builtin_id = is_builtin(argv[0])) >= 0)
		g_exit_status = launch_builtin(builtin_id, argv);
	else if (builtin_id == -2)
		return (-1);
	if (builtin_id != -1)
		return (1);
	if (!(tmp = search_path(argv[0])))
	{
		ft_perror(ERR_UNKNOWN_COMMAND);
		return (1);
	}
	free(argv[0]);
	argv[0] = tmp;
	if (!(pid = fork()))
	{
		signal(SIGINT, sigtest);
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
		else if (WIFSIGNALED(g_exit_status))
		{
			g_p_stop_sig = 1;
			g_exit_status = 130;
		}
		else
			g_exit_status = 0;
		
	}
	signal(SIGINT, signal_handler);
	return (1);
}
