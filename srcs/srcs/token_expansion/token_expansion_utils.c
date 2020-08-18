/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:04:43 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/17 14:58:03 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_specialchar_dquote(char c)
{
	if (c == '\\' || c == '$' || c == '\"')
		return (1);
	else
		return (0);
}

size_t	ft_strlen_etokens(char *s)
{
	int		i;
	size_t	maxlen;
	size_t	evar_count;

	i = 0;
	maxlen = 0;
	evar_count = 0;
	while (g_env[i])
	{
		if (ft_strlen(g_env[i]) > maxlen)
			maxlen = ft_strlen(g_env[i]);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			evar_count++;
		i++;
	}
	return (ft_strlen(s) + (evar_count * maxlen) + 1);
}

char	*quoted_redir(char *tk)
{
	if (!ft_strncmp(tk, "\">\"", 4)
		|| !ft_strncmp(tk, "\'>\'", 4))
		return (ft_strdup("\33\127>"));
	else if (!ft_strncmp(tk, "\">>\"", 5)
			|| !ft_strncmp(tk, "\'>>\'", 5))
		return (ft_strdup("\33\127>>"));
	else if (!ft_strncmp(tk, "\"<\"", 4)
			|| !ft_strncmp(tk, "\'<\'", 4))
		return (ft_strdup("\33\127<"));
	return (NULL);
}

int		expand_quote_set_vals(char *tk, t_expand_tk_dt *d, int *check_quote)
{
	*check_quote = 0;
	if ((d->final_token = quoted_redir(tk)))
	{
		d->is_err = 0;
		return (0);
	}
	if (is_quote_only(tk))
		*check_quote = 1;
	if (!(d->final_token = init_expand(&d->qt, &d->ij, &d->pb, tk)))
	{
		d->is_err = 1;
		return (0);
	}
	return (1);
}

char	*return_expand_tk_quote(t_expand_tk_dt *d, int check_quote)
{
	d->final_token[d->ij.b] = '\0';
	return (return_token(&d->final_token, check_quote));
}
