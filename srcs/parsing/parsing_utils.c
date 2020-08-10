/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:28:17 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/10 14:24:42 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		is_special_char(char *s)
{
	if (*s == '<' || *s == '>' || *s == ';'
	|| *s == '|' || !ft_strncmp(">>", s, 2))
		return (1);
	else
		return (0);
}

void	print_prompt(void)
{
	write(2, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	if (!g_open_pipe)
		write(2, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	else
		write(2, PIPE_START_MSG, ft_strlen(PIPE_START_MSG));
	write(2, NC, ft_strlen(NC));
}

char	*first_token(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	if (nav)
		return (char*)nav->content;
	return (NULL);
}
