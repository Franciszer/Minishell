/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:18:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/06 12:19:41 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	modify_path(char *arg, char *var)
{
	t_list	*env_list;
	t_list	*nav;
	char	*to_cmp;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	nav = env_list;
	while (nav)
	{
		to_cmp = (char*)nav->content;
		if (!ft_strncmp(to_cmp , (const char*)var, ft_strlen(var)) && to_cmp[ft_strlen(var) - 1] == '=')
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

int		builtin_cd(char **args)
{
	char	*directory;

	if (!(directory = getcwd(NULL, 0)))
		return (1);
	if (chdir(args[1]) < 0)
	{
		free(directory);
		ft_perror(strerror(errno));
		return(1);
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
	return(0);
}
