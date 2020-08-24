/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 15:19:50 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/24 16:05:06 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!(body = get_env(key, 0)))
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

char	*eev2(char *token, char *final_token, int *i, int *j)
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
	if (!(body = get_env(key, 1)))
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
