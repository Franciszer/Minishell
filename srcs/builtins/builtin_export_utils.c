/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:43:08 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/26 12:23:34 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*remove_plus_sign(char *arg)
{
	char	*new_arg;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(new_arg = malloc(sizeof(char) * (ft_strlen(arg) + 1))))
		return (NULL);
	while (arg[i])
	{
		if (arg[i] != '+')
			new_arg[j++] = arg[i++];
		else
			i++;
	}
	new_arg[j] = '\0';
	return (new_arg);
}

t_list		*replance_envvar_init_vals(int *replaced)
{
	t_list	*env_list;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (NULL);
	*replaced = 0;
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	g_env_modified = 1;
	return (env_list);
}

int			replace_envvar_util(t_list *nav, char *arg)
{
	char	*current_env;
	size_t	len;

	current_env = (char*)nav->content;
	len = ft_strlen(current_env);
	if (current_env[len - 1] != '=' &&\
		!ft_strncmp(current_env, arg, ft_strlen(current_env)))
	{
		free(nav->content);
		if (!(nav->content = ft_strdup(arg)))
			return (-1);
		return (1);
	}
	return (0);
}
