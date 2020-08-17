/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 15:11:34 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/16 11:17:30 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				red_putfile(t_redir red, int (*pipefd)[2])
{
	int fd;

	if (red.putendfile)
	{
		if ((fd = open(red.file, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
			return (-1);
		close((*pipefd)[1]);
		(*pipefd)[1] = fd;
	}
	if (red.putfile)
	{
		if ((fd = open(red.file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			return (-1);
		close((*pipefd)[1]);
		(*pipefd)[1] = fd;
	}
	return (0);
}

int				redirection(t_redir red, int (*pipefd)[2], int *save)
{
	int		fd;

	if (red.file == NULL)
		return (0);
	if (red.in)
	{
		if ((fd = open(red.file, O_RDONLY)) == -1)
			return (-1);
		if (*save)
			close(*save);
		*save = fd;
	}
	if (red_putfile(red, pipefd))
		return (-1);
	free(red.file);
	if (red.file && red.in == 0 && red.putfile == 0 && red.putendfile == 0)
		return (1);
	return (0);
}

void			check_file(char **file)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strncmp(*file, "\33\127>", 4))
		tmp = ft_strdup("\'>\'");
	else if (!ft_strncmp(*file, "\33\127>>", 5))
		tmp = ft_strdup("\'>>\'");
	else if (!ft_strncmp(*file, "\33\127<", 4))
		tmp = ft_strdup("\'<\'");
	if (tmp)
	{
		free(*file);
		*file = tmp;
	}
}
