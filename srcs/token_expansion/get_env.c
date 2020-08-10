/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:49:23 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 14:21:34 by frthierr         ###   ########.fr       */
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

char	*preprocess_env(char *env_val)
{
	char	*preproc_env;
	int		i;
	int		j;
	int		prev_is_space;

	if (!env_val)
		return (NULL);
	i = -1;
	j = 0;
	prev_is_space = 0;
	preproc_env = (char *)malloc((ft_strlen(env_val) + 1) * sizeof(char));
	while (env_val[++i])
	{
		if (!(env_val[i] == ' ' && prev_is_space == 1))
			preproc_env[j++] = env_val[i];
		if (env_val[i] == ' ')
			prev_is_space = 1;
		else
			prev_is_space = 0;
	}
	preproc_env[j] = '\0';
	free(env_val);
	return (preproc_env);
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
			return (preprocess_env(value));
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
		if (key_start[0] == '$' && key_start[1] == '?')
			return (2);
		else if (!ft_isalnum(key_start[i]))
			return (i);
		else if (ft_isdigit(key_start[i]))
			return (++i);
		else
			i++;
	}
	return (i);
}

char	*eev(char *token, char *final_token, int *i, int *j)
{
	char	*key;
	char	*head;
	char	*body;
	char	*tail;

	final_token[*j] = 0;
	if (!(key = ft_strndup(&token[*i], ft_strlen_key(&token[*i]))))
		return (NULL);
	if (!(head = ft_strdup(final_token)))
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
