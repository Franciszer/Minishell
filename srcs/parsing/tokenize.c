/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franciszer <franciszer@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:27:14 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/04 15:54:56 by franciszer       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token(char *tokenStart, t_list **tokenlist)
{
	size_t	token_len;
	char	*token;
	
	if (isSpecialChar(tokenStart))
		token_len = token_len_special(tokenStart);
	else if (*tokenStart == '\'')
		token_len = tokenLenSQuote(tokenStart);
	else if (*tokenStart == '\"')
		token_len = tokenLenDQuote(tokenStart);
	else
		token_len = tokenLen(tokenStart);
	if (!(token = ft_strndup((const char*)tokenStart, token_len)))
		return (0);
	if (!add_to_token_list(token, tokenlist))
		return (0);
	return (token_len);
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
