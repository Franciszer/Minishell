/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:49:23 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 17:11:56 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key, char **env)
{
	char	*value;
	int		i;

	i = 0;
	if (*key == '$')
		key++;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key)) && env[i][ft_strlen(key)] == '=')
		{
			if (!(value = ft_strdup(&env[i][ft_strlen(key) + 1])))
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
	int	is_nb;

	i = 1;
	is_nb = 0;
	while (key_start[i])
	{
		if (!ft_isalnum(key_start[i]))
			return (i);
		if (ft_isdigit(key_start[i]))
			return (++i);
		i++;
	}
	return (i);
}

char	*expand_env(char *token, int *i, int *j, char **env)
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
	if (!(body = get_env(key, env)))
		body = ft_strdup("");
	*i += ft_strlen_key(&token[*i]);
	*j += ft_strlen(body);
	free(key);
	if (!(head = ft_strjoin_2free(head, body)))
		return (NULL);
	if (!(head = ft_strjoin_2free(head, tail)))
		return (NULL);
	return (head);
}
