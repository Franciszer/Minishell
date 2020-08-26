/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:49:23 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/26 13:26:52 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote_only(char *tk)
{
	if ((ft_strlen(tk) == 2 && (!ft_strncmp(tk, "\"\"", 3)
		|| !ft_strncmp(tk, "\'\'", 3)))
		|| (tk[0] == '\"' && tk[ft_strlen(tk) - 1] == '\"'\
		&& ft_strlen(tk) >= 2))
		return (1);
	return (0);
}

char	*get_env(char *key)
{
	char	*value;
	int		i;

	i = 0;
	if (!key)
		return (NULL);
	if (*key == '$')
		key++;
	if (*key == '?')
		return (ft_itoa(g_exit_status));
	while (g_env[i])
	{
		if (!ft_strncmp(key, g_env[i], ft_strlen(key))
			&& g_env[i][ft_strlen(key)] == '=')
		{
			if (!(value = ft_strdup(&g_env[i][ft_strlen(key) + 1])))
				return (NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

int		ft_strlen_key(char *key_start)
{
	int	i;

	i = 0;
	if (key_start[i] == '$')
		i++;
	if (ft_isdigit(key_start[i]))
		return (++i);
	while (key_start[i])
	{
		if (key_start[0] == '$' && key_start[1] == '?')
			return (2);
		else if (!ft_isalnum(key_start[i]))
			return (i);
		else
			i++;
	}
	return (i);
}
