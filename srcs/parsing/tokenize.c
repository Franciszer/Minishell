/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:27:14 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/09 18:34:34 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token(char *token_start, t_list **tokenlist)
{
	size_t	token_lenv;
	char	*token;

	if (is_special_char(token_start))
		token_lenv = token_len_special(token_start);
	else if (*token_start == '\'')
		token_lenv = token_len_s_quote(token_start);
	else if (*token_start == '\"')
		token_lenv = token_len_d_quote(token_start);
	else
		token_lenv = token_len(token_start);
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

t_list	*tokenize(char *line)
{
	t_list	*tokenlist;
	size_t	i;
	size_t	inc_val;

	tokenlist = (t_list *)0;
	i = 0;
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
	return (tokenlist);
}
