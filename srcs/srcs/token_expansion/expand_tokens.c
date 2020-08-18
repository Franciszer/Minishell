/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/17 14:57:46 by frthierr         ###   ########.fr       */
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

char	*expand_token_quote(char *tk, t_expand_tk_dt d)
{
	int		check_quote;

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
				if (!(d.final_token = eev(tk, d.final_token, &d.ij.a, &d.ij.b)))
					return (return_token(NULL, check_quote));
				if (elif_loop(&d.final_token, &d.tmp))
					return (return_token(&d.final_token, check_quote));
			}
			else
				d.final_token[d.ij.b++] = tk[d.ij.a++];
		else if (!(d.pb = 0))
			else_loop(tk, &d.final_token, &d.ij, &d.qt);
	}
	return (return_expand_tk_quote(&d, check_quote));
}

void	*get_final_token(void *content)
{
	char			*str;
	t_expand_tk_dt	d;

	d.qt.q = -1;
	str = ((char*)content);
	str = expand_token_quote(str, d);
	if (!str || !str[0])
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
