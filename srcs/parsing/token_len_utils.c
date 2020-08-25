/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:04:23 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/25 11:52:10 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		token_len_special(char *tok_s)
{
	if (tok_s[0] == '>' && tok_s[1] && tok_s[1] == '>')
		return (2);
	else if (*tok_s == '|' || *tok_s == '>' || *tok_s == '<' ||
			*tok_s == ';')
		return (1);
	return (0);
}
