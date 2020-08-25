/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:27:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 12:41:40 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_values(int *i, int *pb, int *qt_q, int *qt_dq)
{
	*i = 0;
	*pb = 0;
	*qt_q = -1;
	*qt_dq = -1;
	return (0);
}

static void	set_values_2(char *tk_i, int *qt_q, int *qt_dq, int pb)
{
	*tk_i == '\"' && *qt_q == -1 && !pb ? *qt_dq *= -1 : 0;
	*tk_i == '\'' && *qt_dq == -1 && (!pb || *qt_q == 1) ? *qt_q *= -1 : 0;
}

static int	return_i_or_len(int i, size_t len)
{
	if (i == 0)
		return (len);
	return (i);
}

size_t		ftoken_len(char *tk)
{
	int			i;
	int			pb;
	t_quotes	qt;
	size_t		len;

	len = set_values(&i, &pb, &qt.q, &qt.dq);
	while (tk[i])
	{
		set_values_2(&tk[i], &qt.q, &qt.dq, pb);
		if (qt.q == -1 && qt.dq == -1 && !pb)
		{
			if (tk[i] == ' ')
				return (i);
			if ((len = token_len_special(&tk[i])))
				return (return_i_or_len(i, len));
		}
		if (tk[i] == '\\' && pb == 0 && tk[i + 1] && qt.q == -1 && ++i)
			pb = 1;
		else
		{
			i++;
			pb = 0;
		}
	}
	return (i);
}