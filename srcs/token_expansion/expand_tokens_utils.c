/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:23:52 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/08/25 15:06:16 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_expand(t_quotes *qt, t_int2 *ij, int *pb, char *tk)
{
	char		*final_token;

	qt->q = -1;
	qt->dq = -1;
	ij->a = 0;
	ij->b = 0;
	*pb = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * ft_strlen_etokens(tk))))
		return (NULL);
	return (final_token);
}

int		if_loop(char *tk, t_int2 *ij, t_quotes *qt, int *pb)
{
	tk[ij->a] == '\"' && qt->q == -1 ? qt->dq *= -1 : 0;
	if (tk[ij->a] == '\\' && tk[ij->a + 1] && qt->q == -1 && ++ij->a)
	{
		*pb = 1;
		return (1);
	}
	else if ((tk[ij->a] == '\'' && qt->dq == -1)
			|| (tk[ij->a] == '\"' && qt->q == -1))
	{
		ij->a++;
		return (1);
	}
	return (0);
}

char	*elif_loop(char **final_token, char **tmp)
{
	free(*tmp);
	if (!(*final_token))
	{
		*final_token = ft_strdup("");
		return (*final_token);
	}
	if (!(*final_token)[0])
		return (*final_token);
	return (NULL);
}

void	else_loop(char *tk, char **final_token, t_int2 *ij, t_quotes *qt)
{
	if (!is_specialchar_dquote(tk[ij->a]) && qt->dq == 1)
		(*final_token)[ij->b++] = '\\';
	(*final_token)[ij->b++] = tk[ij->a++];
}

int		elif_test(char *tk, t_quotes qt, t_int2 ij)
{
	if (qt.q == -1 && tk[ij.a] == '$' && tk[ij.a + 1] &&
		(ft_isalnum(tk[ij.a + 1]) || tk[ij.a + 1] == '?'))
		return (1);
	return (0);
}
