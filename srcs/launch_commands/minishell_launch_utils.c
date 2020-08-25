/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 00:58:12 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/24 18:39:07 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		path_searching(char **argv, char **tmp)
{
	if (!(*tmp = search_path(argv[0])))
	{
		g_exit_status = 127;
		ft_perror(ERR_UNKNOWN_COMMAND);
		return (1);
	}
	return (0);
}

int		redir_error(t_redir redir)
{
	int		type;

	type = 0;
	if ((!ft_strlen(redir.file) && (redir.in
		|| redir.putendfile || redir.putfile))
		|| (type = is_redir(redir.file)))
	{
		g_exit_status = 2;
		if (type == 1)
			ft_perror(ERR_REDIR_1);
		else if (type == 2)
			ft_perror(ERR_REDIR_2);
		else if (type == 3)
			ft_perror(ERR_REDIR_3);
		else
			ft_perror(ERR_REDIR);
		return (1);
	}
	else if (is_dir(redir))
	{
		return (1);
	}
	return (0);
}

void	parent(pid_t *pid, int *save, int fd[2])
{
	waitpid(*pid, &g_exit_status, 0);
	*save = fd[0];
	close(fd[1]);
	g_in_fork = 0;
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
	{
		g_p_stop_sig = 1;
		if (g_exit_status != 131)
			g_exit_status += 128;
	}
}

void	child(t_int2 save_last, int contain_putfile,
				char ***argv, int fd[2])
{
	int		builtin_id;

	dup2(save_last.a, 0);
	if (!save_last.b || contain_putfile)
		dup2(fd[1], 1);
	close(fd[0]);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	if ((builtin_id = is_builtin_child((*argv)[0])) >= 0)
	{
		g_exit_status = launch_builtin_child(builtin_id, (*argv));
		fclose(stdout);
		exit(g_exit_status);
	}
	else if (execve((*argv)[0], (*argv), g_env) == -1)
		ft_perror(ERR_EXECVE);
}

int		preprocess_minishell(char ***argv)
{
	int				builtin_id;
	char			*tmp;

	builtin_id = -1;
	if (!((*argv)[1] && is_redir((*argv)[1]))\
		&& (builtin_id = is_builtin_parent((*argv))) >= 0)
		g_exit_status = launch_builtin_parent(builtin_id, (*argv));
	else if (builtin_id == -2)
		return (-1);
	if (builtin_id != -1 || path_searching((*argv), &tmp))
		return (1);
	free((*argv)[0]);
	(*argv)[0] = tmp;
	return (0);
}
