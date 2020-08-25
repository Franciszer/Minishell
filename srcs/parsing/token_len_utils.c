/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:04:23 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/24 18:40:27 by qfeuilla         ###   ########.fr       */
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

size_t		token_len_env(char *tok_s)
{
	int		i;

	i = 0;
	while (tok_s[++i])
	{
		if (tok_s[i] == ' ' || token_len_special(&tok_s[i]) || tok_s[i] == '$' || is_quote(tok_s[i]))
            return (i);
	}
	return (i);
}
