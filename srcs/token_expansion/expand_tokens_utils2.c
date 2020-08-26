/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:53:56 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/26 16:41:20 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_token(char **tk, int check_quote)
{
	if ((!(*tk) || !(*tk)[0]) && check_quote)
	{
		if (*tk)
			free(*tk);
		return (ft_strdup("\33\127"));
	}
	return (*tk);
}

int		expand_token_dquote_return(t_expand_tk_dt *d, char *tk)
{
	if (!(d->final_token = eev(tk, d->final_token, &d->ij.a, &d->ij.b)))
		return (1);
	if (elif_loop(&d->final_token, &d->tmp))
		return (2);
	return (0);
}

char	*expand_token_quote(char *tk, t_expand_tk_dt d)
{
	int		check_quote;
	int		ret;

	if (!expand_quote_set_vals(tk, &d, &check_quote))
		return (!d.is_err ? d.final_token : return_token(NULL, check_quote));
	while (tk[d.ij.a])
	{
		tk[d.ij.a] == '\'' && d.qt.dq == -1 && (!d.pb || d.qt.q == 1)
				? d.qt.q *= -1 : 0;
		if (!d.pb || d.qt.q == 1)
			if (if_loop(tk, &d.ij, &d.qt, &d.pb))
				d.final_token = d.final_token;
			else if (elif_test(tk, d.qt, d.ij))
			{
				d.tmp = d.final_token;
				if ((ret = expand_token_dquote_return(&d, tk)))
					return (ret == 1 ? return_token(NULL, check_quote) :\
					return_token(&d.final_token, check_quote));
			}
			else
				d.final_token[d.ij.b++] = tk[d.ij.a++];
		else if (!(d.pb = 0))
			else_loop(tk, &d.final_token, &d.ij, &d.qt);
	}
	return (return_expand_tk_quote(&d, check_quote));
}
