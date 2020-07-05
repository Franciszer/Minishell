/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:04:43 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/05 10:38:17 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes_free(char *str, char quote)
{
	char	*new;
	size_t	len;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	if (*str == quote)
		i = 1;
	len = ft_strlen(&str[i]);
	if (str[len] == quote)
		len--;
	if (!(new = ft_strndup(&str[i], len)))
		return (NULL);
	return (new);
}

int		is_specialchar_dquote(char c)
{
	if (c == '\\' || c == '$' || c == '\"')
		return (1);
	else
		return (0);
}

size_t	ft_strlen_etokens(char *s)
{
	int		i;
	size_t	maxlen;
	size_t	evar_count;
	
	i = 0;
	maxlen = 0;
	evar_count = 0;
	while (g_env[i])
	{
		if (ft_strlen(g_env[i]) > maxlen)
			maxlen = ft_strlen(g_env[i]);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			evar_count++;
		i++;
	}
	return (ft_strlen(s) + (evar_count * maxlen) + 1);
}
