/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:43:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/02 16:57:16 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokens_syntax_check(t_list *token_list)
{
	t_list	*nav;
	char	*str;

	nav = token_list;
	while (nav)
	{
		str = (char*)nav->content;
		if (!ft_strlen(str) || (isQuote(str[0]) && ft_strlen(str) == 1) ||\
			((str[0] == '\''	&& str[ft_strlen(str) -1] != '\'') ||\
			(str[0] == '\"'	&& str[ft_strlen(str) -1] != '\"')))
			return (0);
		nav = nav->next;
	}
	return (1);
}
