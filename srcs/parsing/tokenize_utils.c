/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 23:03:21 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/26 15:04:34 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_quotes(t_expand_tk_dt *d, char *tk)
{
	tk[(*d).ij.a] == '\"' && (*d).qt.q == -1 && !(*d).pb
		? d->qt.dq *= -1 : 0;
	tk[(*d).ij.a] == '\'' && (*d).qt.dq == -1 && !(*d).pb
		? d->qt.q *= -1 : 0;
}

int		manage_tmp(t_expand_tk_dt *d, char *tmp, char *tk)
{
	free(d->final_token);
	d->final_token = tmp;
	do_quotes(d, tk);
	if (!d->final_token[0])
		return (0);
	return (1);
}
