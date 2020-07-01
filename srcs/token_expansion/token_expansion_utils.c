/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:04:43 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 17:04:39 by frthierr         ###   ########.fr       */
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
