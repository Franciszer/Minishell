/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:27:14 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/25 17:38:50 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token(char *token_start, t_list **tokenlist)
{
	size_t	token_lenv;
	char	*token;

	token_lenv = ftoken_len(token_start);
	if (!(token = ft_strndup((const char*)token_start, token_lenv)))
		return (0);
	if (!add_to_token_list(token, tokenlist))
		return (0);
	return (token_lenv);
}

int		add_to_token_list(char *token, t_list **tokenlist)
{
	t_list	*new;

	if (!(new = ft_lstnew((void*)token)))
		return (0);
	ft_lstadd_back(tokenlist, new);
	return (1);
}

int		expand_quote_set_vals_env(char *tk, t_expand_tk_dt *d)
{
	if (!(d->final_token = init_expand(&d->qt, &d->ij, &d->pb, tk)))
	{
		d->is_err = 1;
		return (0);
	}
	return (1);
}

char	*expand_env_var(char *tk, t_expand_tk_dt d)
{
	char	*tmp;

	if (!expand_quote_set_vals_env(tk, &d))
		return (!d.is_err ? d.final_token : NULL);
	while (tk[d.ij.a])
	{
		tk[d.ij.a] == '\'' && d.qt.dq == -1 && (!d.pb || d.qt.q == 1)
				? d.qt.q *= -1 : 0;
		tk[d.ij.a] == '\"' && d.qt.q == -1 && !d.pb
				? d.qt.dq *= -1 : 0;
		if (d.qt.q == -1 && tk[d.ij.a] == '$' && tk[d.ij.a + 1] &&
			!d.pb && ft_isalnum(tk[d.ij.a + 1]))
		{
			if (!(tmp = eev(tk, d.final_token, &d.ij.a, &d.ij.b)))
				return (NULL);
			else
			{
				free(d.final_token);
				d.final_token = tmp;
			}
		}
		if (tk[d.ij.a] == '\\' && !d.pb && d.qt.q == -1)
			d.pb = 1;
		else
			d.pb = 0;
		if (tk[d.ij.a] && !(!d.pb && tk[d.ij.a] == '$' && d.qt.q == -1 && tk[d.ij.a + 1]))
			d.final_token[d.ij.b++] = tk[d.ij.a++];
	}
	d.final_token[d.ij.b] = '\0';
	return (d.final_token);
}

t_list	*tokenize(char *line)
{
	t_list			*tokenlist;
	size_t			i;
	size_t			inc_val;
	t_expand_tk_dt	d;
	char			*tmp;

	d.qt.q = -1;
	tokenlist = (t_list *)0;
	i = 0;
	tmp = expand_env_var(line, d);
	line = tmp;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			if ((inc_val = get_token(&line[i], &tokenlist)) == 0)
				return (NULL);
			i += inc_val;
		}
		else
			i++;
	}
	free(tmp);
	return (tokenlist);
}
