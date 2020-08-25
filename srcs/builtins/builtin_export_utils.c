/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:43:08 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 15:13:04 by qfeuilla         ###   ########.fr       */
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
