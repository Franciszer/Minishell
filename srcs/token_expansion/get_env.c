/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:49:23 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 10:59:27 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key)
{
	char	*value;
	int		i;

	i = 0;
	if (!key)
		return (NULL);
	if (*key == '$')
		key++;
	while (g_env[i])
	{
		if (!ft_strncmp(key, g_env[i], ft_strlen(key)) && g_env[i][ft_strlen(key)] == '=')
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
	while (key_start[i])
	{
		if (i == 0 && key_start[i] == '$')
			i++;
		else if (!ft_isalnum(key_start[i]))
			return (i);
		else if (ft_isdigit(key_start[i]))
			return (++i);
		else
			i++;
	}
	return (i);
}

char	*expand_env(char *token, int *i, int *j)
{
	char	*key;
	char	*head;
	char	*body;
	char	*tail;

	if (!(key = ft_strndup(&token[*i], ft_strlen_key(&token[*i]))))
		return (NULL);
	if (!(head = ft_strndup(token, *i)))
		return (NULL);
	if (!(tail = ft_strdup(&token[*i + ft_strlen_key(&token[*i])])))
		return (NULL);
	if (!(body = get_env(key)))
		body = ft_strdup("");
	if (!(!head[0] && !body[0] && !tail[0]))
		*i += ft_strlen_key(&token[*i]);
	*j += ft_strlen(body);
	free(key);
	if (!(head = ft_strjoin_2free(head, body)))
		return (NULL);
	if (!(head = ft_strjoin_2free(head, tail)))
		return (NULL);
	return (head);
}
