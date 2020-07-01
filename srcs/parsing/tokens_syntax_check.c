/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_syntax_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:43:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/01 18:43:41 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokens_syntax_check(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	while (nav)
	{
		if (!ft_strlen((char*)nav->content) ||\
			((((char*)nav->content)[0] == '\''	&& ((char*)nav->content)[ft_strlen((char*)nav->content) -1] != '\'') ||\
			(((char*)nav->content)[0] == '\"'	&& ((char*)nav->content)[ft_strlen((char*)nav->content) -1] != '\"')))
			return (0);
		nav = nav->next;
	}
	return (1);
}
