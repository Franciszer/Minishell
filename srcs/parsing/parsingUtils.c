/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:28:17 by frthierr          #+#    #+#             */
/*   Updated: 2020/06/26 10:24:14 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isQuote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		isSpecialChar(char *s)
{
	if (*s == '<' || *s == '>' || *s == ';'
	|| *s == '|' || !ft_strncmp(">>", s, 2))
		return (1);
	else
		return (0);	
}
