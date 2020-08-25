/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:05:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 12:46:37 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_go_home(char *current_dir)
{
	char	**new;
	char	*home;
	int		return_value;
	char	*check_home;

	if (!(check_home = get_env("HOME")))
		return (1);
	if (!ft_strncmp(check_home, current_dir, ft_strlen(current_dir) + 1))
		return_value = 0;
	else
	{
		if (!(new = malloc(sizeof(char*) * 3)))
			return (1);
		if (!(new[0] = ft_strdup("cd")))
			return (1);
		if (!(home = get_env("HOME")))
			return (1);
		new[1] = home;
		new[2] = NULL;
		return_value = builtin_cd(new);
		free_argv(new, INT_MAX);
	}
	free(check_home);
	free(current_dir);
	return (return_value);
}
