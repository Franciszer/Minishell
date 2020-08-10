/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:02:44 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 13:48:29 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*get_pathcommand(char *path, char *command)
{
	char	*pathcommand;

	if (ft_strlen(path) && path[ft_strlen(path) - 1] != '/')
	{
		if (!(pathcommand = ft_strjoin(path, "/")))
			return (NULL);
		return (ft_strjoin_free(pathcommand, command));
	}
	else
		return (ft_strjoin(path, command));
}

static char		*search_relativepath(char *command)
{
	char	*path;

	if (!(path = get_env("PWD")))
		return (NULL);
	if (path[ft_strlen(path) - 1] != '/')
	{
		if (!(path = ft_strjoin_free(path, "/")))
			return (NULL);
	}
	if (!(path = ft_strjoin_free(path, command)))
		return (NULL);
	if (open(path, O_CLOEXEC) == -1)
	{
		free(path);
		return (NULL);
	}
	else
		return (path);
}

static char		*return_free_av(char *ret, char ***path_array, char **path)
{
	free_argv(*path_array, INT_MAX);
	free(*path);
	return (ret);
}

int				is_custom(char *command)
{
	if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1)
		|| !ft_strncmp(command, "env", ft_strlen("env") + 1)
		|| !ft_strncmp(command, "echo", ft_strlen("echo") + 1)
		|| !ft_strncmp(command, "export", ft_strlen("export") + 1))
		return (1);
	return (0);
}

char			*search_path(char *command)
{
	char	*path;
	char	**path_array;
	char	*command_path;
	int		i;

	if (is_custom(command))
		return (ft_strdup(command));
	if (!(path = get_env("PATH"))
		|| !(path_array = ft_split(path, ':')))
		return (NULL);
	i = 0;
	while (path_array[i])
	{
		if (!(command_path = get_pathcommand(path_array[i], command)))
			return (NULL);
		if (open(command_path, O_CLOEXEC) != -1)
			return (return_free_av(command_path, &path_array, &path));
		free(command_path);
		i++;
	}
	if (open(command, O_CLOEXEC) != -1)
		return (ft_strdup(command));
	if ((command_path = search_relativepath(command)))
		return (command_path);
	return (return_free_av(NULL, &path_array, &path));
}
