/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:27:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 15:12:59 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_len(char *tok_s)
{
	t_size_t2	il;
	int			p_back;

	il.a = 0;
	il.b = 0;
	p_back = 0;
	while (tok_s[il.a])
	{
		if (((is_quote(tok_s[il.a]) || is_special_char(&tok_s[il.a]))
			|| ft_isspace(tok_s[il.a])) && !p_back)
		{
			if (tok_s[il.a] == '\'')
				return (il.b + token_len_s_quote(&tok_s[il.a]));
			if (tok_s[il.a] == '\"')
				return (il.b + token_len_d_quote(&tok_s[il.a]));
			return (il.b);
		}
		if (tok_s[il.a] == '\\')
			p_back = 1;
		else
			p_back = 0;
		il.a++;
		il.b++;
	}
	return (il.b);
}

size_t	token_len_s_quote(char *tok_s)
{
	size_t	i;

	i = 1;
	while (tok_s[i])
	{
		if (tok_s[i] == '\'')
		{
			if (tok_s[i + 1] &&
				!is_special_char(&tok_s[i + 1]) && tok_s[i + 1] != ' ')
			{
				if (*tok_s == '\'' && ++i)
					return (i + token_len_s_quote(&tok_s[i]));
				else if (*tok_s == '\"' && ++i)
					return (i + token_len_d_quote(&tok_s[i]));
				else if (++i)
					return (i + token_len(&tok_s[i]));
			}
			else
				return (++i);
		}
		i++;
	}
	return (i);
}

size_t	token_len_d_quote_ret(size_t i, char *tok_s)
{
	if (tok_s[i + 1] && !is_special_char(&tok_s[i + 1])
		&& tok_s[i + 1] != ' ')
	{
		if (*tok_s == '\'' && ++i)
			return (i + token_len_s_quote(&tok_s[i]));
		else if (*tok_s == '\"' && ++i)
			return (i + token_len_d_quote(&tok_s[i]));
		else if (++i)
			return (i + token_len(&tok_s[i]));
	}
	else
		return (++i);
	return (0);
}

size_t	token_len_d_quote(char *tok_s)
{
	size_t	i;
	int		p_back;
	size_t	ret;

	i = 1;
	p_back = 0;
	while (tok_s[i])
	{
		if (tok_s[i] == '\"' && !p_back)
		{
			if ((ret = token_len_d_quote_ret(i, tok_s)))
				return (ret);
		}
		if (tok_s[i] == '\\')
			p_back = 1;
		else
			p_back = 0;
		i++;
	}
	return (i);
}

size_t	token_len_special(char *tok_s)
{
	if (tok_s[0] == '>' && tok_s[1] && tok_s[1] == '>')
		return (2);
	else if (*tok_s == '|' || *tok_s == '>' || *tok_s == '<' ||
			*tok_s == ';')
		return (1);
	return (0);
}
