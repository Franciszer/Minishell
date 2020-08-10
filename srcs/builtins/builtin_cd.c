/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:18:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 14:18:32 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			modify_path(char *arg, char *var)
{
	t_list	*env_list;
	t_list	*nav;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	nav = env_list;
	while (nav)
	{
		if (!ft_strncmp((char*)nav->content, (const char*)var, ft_strlen(var))
			&& ((char*)nav->content)[ft_strlen(var) - 1] == '=')
		{
			free(nav->content);
			if (!(nav->content = ft_strjoin(var, arg)))
				return (1);
		}
		nav = nav->next;
	}
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	else
		g_env_modified = 1;
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	ft_lstclear(&env_list, free);
	return (0);
}

static int			backtrack_dirs(void)
{
	size_t	i;
	char	*current_dir;
	char	*new_dir;

	if (!(current_dir = get_env("PWD")))
		return (1);
	if (modify_path(current_dir, "OLDPWD="))
		return (1);
	i = ft_strlen(current_dir) - 1;
	while (i > 1 && current_dir[i] == '.' && current_dir[i - 1] == '/')
		i -= 2;
	while (current_dir[i] != '/')
		i--;
	if (!(new_dir = ft_strndup_free(current_dir, i)))
		return (1);
	if (modify_path(new_dir, "PWD="))
		return (1);
	chdir(new_dir);
	free(new_dir);
	return (0);
}

static int			handle_deleted_dir(char *arg)
{
	char	*current_dir;
	char	*new_dir;

	if (!ft_strncmp(arg, "..", 3))
		return (backtrack_dirs());
	if (!(current_dir = get_env("PWD")))
		return (1);
	if (modify_path(current_dir, "OLDPWD="))
		return (1);
	if (!(new_dir = ft_strjoin_free(current_dir, "/.")))
		return (1);
	if (modify_path(new_dir, "PWD="))
		return (1);
	return (0);
}

char				*is_working_dir(void)
{
	DIR		*dir;
	char	*current_dir;

	if (!(current_dir = get_env("PWD")))
		return (NULL);
	if (!(dir = opendir((const char*)current_dir)))
		return (NULL);
	closedir(dir);
	return (getcwd(NULL, 0));
}

int					builtin_cd(char **args)
{
	char	*directory;

	if (args[0] && args[1] && args[2])
		return (ft_perror("too many arguments") == 0 ? 1 : 1);
	if (!(directory = getcwd(NULL, 0)))
		return (handle_deleted_dir(args[1]));
	if (!args[1])
		return (ft_go_home(directory));
	if (chdir(args[1]) < 0)
	{
		free(directory);
		return (ft_perror(strerror(errno)) == 0 ? 1 : 1);
	}
	else
	{
		if (modify_path(directory, "OLDPWD="))
			return (1);
		free(directory);
		if (!(directory = getcwd(NULL, 0)))
			return (1);
		if (modify_path(directory, "PWD="))
			return (1);
		free(directory);
	}
	return (0);
}
