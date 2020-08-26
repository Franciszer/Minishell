/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/26 16:41:15 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fast_tokenize(char *tk, t_expand_tk_dt d)
{
	int		psp;
	int		save;

	psp = 0;
	if (!expand_quote_set_vals_env(tk, &d))
		return (!d.is_err ? d.final_token : NULL);
	while (tk[d.ij.a])
	{
		do_quotes(&d, tk);
		if (((save = d.ij.a) + 1) && !((psp || d.ij.a == 0)\
		&& tk[d.ij.a] == ' ' && d.qt.q == -1 && d.qt.dq == -1))
			d.final_token[d.ij.b++] = tk[d.ij.a++];
		else
			d.ij.a++;
		d.pb = (tk[save] == '\\' && !d.pb && d.qt.q == -1) ? 1 : 0;
		psp = (tk[save] == ' ') ? 1 : 0;
	}
	if (d.ij.b - 1 >= 0 && d.final_token[d.ij.b - 1] == ' ')
		d.final_token[d.ij.b - 1] = '\0';
	d.final_token[d.ij.b] = '\0';
	return (d.final_token);
}

char	*expand_env_var(char *tk, t_expand_tk_dt d)
{
	char	*tmp;
	int		save;

	if (!expand_quote_set_vals_env(tk, &d))
		return (!d.is_err ? d.final_token : NULL);
	while (tk[d.ij.a])
	{
		do_quotes(&d, tk);
		if (!d.pb && d.qt.q == -1 && tk[d.ij.a] == '$' && tk[d.ij.a + 1]
			&& ft_isalnum(tk[d.ij.a + 1]))
		{
			if (!(tmp = eev(tk, d.final_token, &d.ij.a, &d.ij.b)))
				return (NULL);
			else if (!manage_tmp(&d, tmp, tk))
				return (d.final_token);
		}
		if (((save = d.pb) + 1) && tk[d.ij.a] == '\\' && !d.pb && d.qt.q == -1)
			d.pb = 1;
		else
			d.pb = 0;
		if (tk[d.ij.a] && !(!save && tk[d.ij.a] == '$' && d.qt.q == -1 &&
			tk[d.ij.a + 1] && ft_isalnum(tk[d.ij.a + 1])))
			d.final_token[d.ij.b++] = tk[d.ij.a++];
	}
	return (!(d.final_token[d.ij.b] = '\0') ? d.final_token : d.final_token);
}

void	*get_final_token(void *content)
{
	char			*str;
	t_expand_tk_dt	d;
	char			*tmp;

	d.qt.q = -1;
	str = ((char*)content);
	if ((tmp = expand_env_var(str, d)))
		str = tmp;
	if ((tmp = fast_tokenize(str, d)))
	{
		free(str);
		str = tmp;
	}
	if ((tmp = expand_token_quote(str, d)))
	{
		free(str);
		str = tmp;
	}
	if (!(str = tmp) || !str[0])
	{
		if (str)
			free(str);
		return (NULL);
	}
	return (str);
}

void	clear_token(t_list **token_list)
{
	t_list *nav;
	t_list **tmp;

	nav = *token_list;
	while (nav)
	{
		if (!nav->content)
		{
			tmp = &nav;
			(*tmp) = nav->next;
		}
		else if (!ft_strncmp(nav->content, "\33\127", ft_strlen("\33\127") + 1))
		{
			free(nav->content);
			nav->content = ft_strdup("");
		}
		nav = nav->next;
	}
}

t_list	*expand_tokens(t_list *token_list)
{
	t_list	*expanded_list;
	t_list	*tmp_list;

	tmp_list = token_list;
	if (token_list && token_list->content &&\
	((char*)(token_list->content))[0] == '$')
		g_first_is_envvar = 1;
	expanded_list = ft_lstfilter(&tmp_list, get_final_token, free);
	clear_token(&expanded_list);
	return (expanded_list);
}
