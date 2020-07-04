/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:02:44 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 18:48:09 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pathcommand(char *path, char *command)
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

static char	*search_relativepath(char *command, char **env)
{
	char	*path;

	if (!(path = get_env("PWD", env)))
		return (NULL);
	if (path[ft_strlen(path - 1)] != '/')
	{
		if (!(path = ft_strjoin_free(path, "/")))
			return (NULL);
	}
	if (!(path = ft_strjoin_free(path, command)))
		return (NULL);
	if (open(path, O_CLOEXEC) == -1)
		return (NULL);
	else
		return (path);
}

char			*search_path(char *command, char **env)
{
	char	*path;
	char	**path_array;
	char	*command_path;
	int		i;

	if (open(command, O_CLOEXEC) != -1)
		return (ft_strdup(command));
	if ((command_path = search_relativepath(command, env)))
		return (command_path);
	if (!(path = get_env("PATH", env)))
		return (NULL);
	if (!(path_array = ft_split(path, ':')))
		return (NULL);
	i = 0;
	while (path_array[i])
	{
		if (!(command_path = get_pathcommand(path_array[i], command)))
			return (NULL);
		if (open(command_path, O_CLOEXEC) != -1)
		{
			free_argv(path_array, INT_MAX);
			free(path);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_argv(path_array, INT_MAX);
	free(path);
	return (NULL);
}