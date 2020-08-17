/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:13:58 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/16 10:17:16 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigtest(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}

char	**copy_argv(char **argv)
{
	int		i;
	int		j;
	char	**argv2;

	i = 0;
	j = -1;
	while (argv[i] != NULL)
		i++;
	argv2 = (char **)malloc(i * sizeof(char *));
	while (++j < i)
		argv2[j] = ft_strdup(argv[j]);
	return (argv2);
}

int		contain_redir(char **argv)
{
	int		i;
	int		type;

	i = 0;
	while (argv[i])
	{
		if ((type = is_redir(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

t_list	*do_redir(char ***argv)
{
	t_redir	*redir;

	redir = (t_redir*)malloc(sizeof(t_redir));
	*redir = stock_redir(*argv);
	if (redir_error(*redir))
	{
		free(redir);
		return (NULL);
	}
	cmd_to_rafter(argv);
	return (ft_lstnew(redir));
}
